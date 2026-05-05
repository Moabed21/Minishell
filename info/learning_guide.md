# Minishell: Pipelines & Heredoc — Learning Guide

> This is not code to copy. This is how to **think** about the problem.

---

## Part 1: Understanding Pipes

### What is `pipe()` really doing?

Think of it as creating a **one-way tunnel** in the OS kernel:

```
pipe(fd)  →  fd[0] = tunnel entrance (read)
              fd[1] = tunnel exit (write)

Whatever you write() to fd[1] can be read() from fd[0]
```

**Critical rule:** The tunnel only works when **the write-end is closed by ALL processes that have it**. Otherwise the reader hangs forever waiting for more data.

### Try this in your head

```bash
ls | grep .c
```

What does bash actually do?

1. Create a tunnel
2. Make `ls` write its output INTO the tunnel instead of the screen
3. Make `grep` read its input FROM the tunnel instead of the keyboard
4. Run both at the same time

That's it. That's the whole pipeline concept.

---

## Part 2: The `prev_fd` Trick

### Why one pipe is enough

With 3 commands: `ls | grep .c | wc -l`

You might think you need 2 pipes alive at the same time. You don't. Think about it like a **relay race** — you pass the baton one hand at a time:

```
Round 1:  [ls] ──writes──► pipe ──► save read-end as "prev_fd"
                           (done with this pipe)

Round 2:  prev_fd ──► [grep] reads from it
          [grep] ──writes──► NEW pipe ──► save read-end as new "prev_fd"
                              (done with this pipe too)

Round 3:  prev_fd ──► [wc] reads from it
          [wc] ──writes──► stdout (no pipe, it's the last command)
```

**`prev_fd` is the baton.** It carries the read-end from the previous round to the next round.

### The questions to answer for EACH command

Walk the linked list. For each node, answer:

| Question | First cmd | Middle cmd | Last cmd |
|----------|-----------|------------|----------|
| Do I need a pipe after me? | Yes (someone reads my output) | Yes | **No** (output goes to screen) |
| Where do I read from? | stdin (default) | `prev_fd` (previous pipe) | `prev_fd` |
| Where do I write to? | pipe write-end | pipe write-end | stdout (default) |

Notice: you never check "am I first/middle/last" explicitly. You just check:
- **`prev_fd != -1`** → means there's a previous pipe to read from
- **`node->next != NULL`** → means there's a next command, so create a pipe

---

## Part 3: The Fork Dance

### What happens in the child vs the parent

After `fork()`, you have **two copies of the same process**. They share the same file descriptors. That's the key.

**Child's job:**
1. Rewire stdin/stdout using `dup2`
2. Close any pipe ends it doesn't need
3. `execve` (never returns)

**Parent's job:**
1. Close the pipe ends it doesn't use (CRITICAL — or the reader hangs)
2. Save `fd[0]` as `prev_fd` for the next iteration
3. Move to the next command

### Why does the parent close fds?

Because after `fork()`, both parent and child have copies of `fd[0]` and `fd[1]`. If the parent doesn't close `fd[1]`, the pipe never signals EOF to the reader — even after the writer child exits.

### Think about it: who has what?

```
After pipe() + fork():

Parent has:  fd[0] (read)  ← save as prev_fd, close later
             fd[1] (write) ← CLOSE immediately (parent doesn't write)

Child has:   fd[0] (read)  ← CLOSE (child doesn't read from its own pipe)
             fd[1] (write) ← dup2 to stdout, then close original
```

---

## Part 4: Waiting for Children

### Why wait for ALL, but only care about the LAST?

```bash
ls | grep .c | wc -l
echo $?    # this shows wc's exit status, NOT ls's or grep's
```

Bash rule: `$?` = exit status of the **last command** in the pipeline.

But you must still `waitpid` for every child. Otherwise they become **zombies** (show up in `ps` as `<defunct>`).

### How to do it

Walk your cmd list. For each cmd that was forked (`fork_id > 0`), call `waitpid`. But only update `shell->last_status` from the **last** one's pid.

---

## Part 5: Heredoc

### What is heredoc?

```bash
cat << EOF
hello world
$USER is logged in
EOF
```

It's just **typing input for a command** interactively, line by line, until a delimiter word is typed.

### How to implement it — think about it as 3 steps

**Step 1: Where does the data go?**

You need the lines typed by the user to become the command's stdin. Just like `< file` redirects a file to stdin, heredoc redirects **typed lines** to stdin.

But you don't have a file. So use a **pipe** — write the lines to the pipe's write-end, and give the read-end to the command as its `fd_in`.

**Step 2: The reading loop**

```
Create pipe
While true:
    line = readline("> ")
    if line is NULL → Ctrl+D, break (warn about EOF)
    if line equals delimiter → break (normal end)
    write line to pipe write-end
    write "\n" to pipe write-end
Close pipe write-end
Set cmd->fd_in = pipe read-end
```

**Step 3: Signals**

This is the tricky part. During heredoc:
- **Ctrl+C** should cancel the heredoc, return to prompt, set `$?` = 130
- **Ctrl+D** should end input with a warning
- **Ctrl+\\** should do nothing

The trick for Ctrl+C: your signal handler **closes stdin** (`close(STDIN_FILENO)`). This makes `readline` return NULL, breaking the loop. Then restore stdin with a backed-up copy (`dup`).

```
Before heredoc:
    stdin_backup = dup(STDIN_FILENO)   ← save a copy
    Install heredoc signal handler

After heredoc:
    dup2(stdin_backup, STDIN_FILENO)   ← restore
    close(stdin_backup)
    Restore interactive signals
```

---

## Part 6: Heredoc + Expander

### The rule

```bash
cat << EOF       # no quotes on delimiter → EXPAND variables
cat << "EOF"     # quotes on delimiter → DON'T expand
cat << 'EOF'     # quotes on delimiter → DON'T expand
```

### What "expand" means

Before writing each line to the pipe, scan it for `$` signs:

```
Input line:    "hello $USER, status is $?"
After expand:  "hello moabed, status is 0"
```

Your partner's `expand_value(line, envp, last_status)` does exactly this:
- Takes a string
- Finds every `$VAR` → looks up in `envp` array → replaces
- Finds `$?` → replaces with `last_status`
- Returns a new allocated string with everything expanded

### Where does it plug in?

```
In your heredoc reading loop:

    line = readline("> ")
    ... check delimiter ...

    IF delimiter was NOT quoted:
        expanded = expand_value(line, shell->envp, shell->last_status)
        free(line)
        write expanded to pipe
        free(expanded)
    ELSE:
        write line to pipe as-is
        free(line)
```

### How to know if delimiter was quoted?

Your parser stores the delimiter in `redir->filename`. You need to either:
1. Check if the original had quotes before stripping (parser's job)
2. Add a flag to `t_redir` like `int quoted` (cleanest)

---

## Part 7: Putting It All Together

### The complete mental model for `multiple_cmds`

```
initialize prev_fd = -1 (no previous pipe)
ignore signals (parent shouldn't die from Ctrl+C)

FOR EACH command in the linked list:

    ┌─ PIPE ────────────────────────────────────┐
    │ If there's a next command → pipe()        │
    │ (creates a tunnel for this cmd's output)  │
    └───────────────────────────────────────────┘

    ┌─ REDIRECTIONS ────────────────────────────┐
    │ Handle > file, < file, >> file, << EOF    │
    │ These may override fd_in / fd_out         │
    │ Heredoc goes here too                     │
    └───────────────────────────────────────────┘

    ┌─ WIRING ──────────────────────────────────┐
    │ If prev_fd exists → cmd reads from it     │
    │ If pipe exists → cmd writes to it         │
    │ (but redirections take priority)          │
    └───────────────────────────────────────────┘

    ┌─ FORK ────────────────────────────────────┐
    │ Child:                                    │
    │   restore default signals                 │
    │   dup2(fd_in → stdin)                     │
    │   dup2(fd_out → stdout)                   │
    │   close unused pipe ends                  │
    │   exec or builtin + exit                  │
    │                                           │
    │ Parent:                                   │
    │   close used fds (fd_in, fd_out if > 2)   │
    │   save pipe read-end as prev_fd           │
    └───────────────────────────────────────────┘

    move to next command

WAIT for all children
restore interactive signals
```

---

## Checklist: Test These Cases

Test each one in bash first, then in your minishell:

```bash
# Basic pipes
ls | cat
ls | grep .c | wc -l
echo hello | cat | cat | cat

# Pipes with builtins
echo hello | cat
export TEST=123 | cat    # export should NOT affect parent in pipeline

# Pipes with redirections
ls | grep .c > output.txt
< input.txt cat | wc -l

# Heredoc
cat << EOF
hello world
EOF

# Heredoc with expansion
export NAME=moabed
cat << EOF
hello $NAME
status is $?
EOF

# Heredoc with Ctrl+C (should return to prompt, $? = 130)
cat << EOF
> hello
> ^C
minishell>

# Heredoc in pipeline
cat << EOF | grep hello
hello world
goodbye world
EOF

# Edge cases
ls | nonexistent_cmd    # $? should be 127
nonexistent_cmd | ls    # ls should still run
```
