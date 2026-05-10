# 🐚 Minishell — Complete Internal Architecture & Evaluation Cheatsheet

## 📦 Project Structure Overview

```
Minishell/
├── headers/
│   ├── libs.h                  ← System includes, macros (BUFFERSIZE, SUCCESS/FAILURE)
│   ├── parsingpart.h           ← Parsing structs: t_token, t_cmd, t_redir + parsing API
│   └── executionpart.h         ← Execution structs: t_env, t_exec + execution API
├── src/
│   ├── tokenizer/
│   │   └── tokenization.c      ← Lexer: raw input → token linked list
│   ├── expander/
│   │   ├── expansion.c         ← $VAR / $? expansion + word splitting
│   │   └── inserting.c         ← Token list manipulation for split words
│   ├── parse/
│   │   ├── parsing.c           ← Token list → command linked list (t_cmd)
│   │   ├── parsing_args.c      ← Extract args array from tokens
│   │   ├── parsing_cmd.c       ← t_cmd node creation, free, traversal
│   │   └── parsing_redir.c     ← Extract redirections → t_redir linked list
│   ├── execution/
│   │   ├── main.c              ← Entry point, REPL loop, prepare_for_execution()
│   │   ├── execution.c         ← Dispatcher: single vs pipeline, fork/pipe helpers
│   │   ├── executeone.c        ← Single command: builtin or fork+execve
│   │   ├── execute-multiple.c  ← Pipeline: pipe chain, fork per stage, wait_all
│   │   ├── heredoc.c           ← Heredoc: pipe+readline loop, $VAR expansion
│   │   ├── io-redir.c          ← Apply >, >>, < redirections via open()
│   │   ├── signals.c           ← SIGINT/SIGQUIT handlers (interactive/ignore/default)
│   │   ├── built-ins.c         ← export (stub)
│   │   ├── built-ins2.c        ← exec_builtin dispatcher, env, exit
│   │   ├── built-ins3.c        ← echo, pwd, unset (stub)
│   │   ├── built-ins4.c        ← cd, replace/get_value env helpers
│   │   └── error-handle.c      ← Free functions, error display, ruin_everything
│   ├── utils/
│   │   ├── e_utils.c           ← ft_strcmp, init_vals (set fd_in=0, fd_out=1)
│   │   ├── e_utils2.c          ← shell_init, g_sig, check_cmds, free2d_array
│   │   ├── env-utils3.c        ← t_env linked list: init, add, ruin
│   │   ├── expansion_utils.c   ← is_var_char, get_env_value, append_char/str
│   │   ├── lexer_utils.c       ← save_op, save_word, is_operator, set_status
│   │   ├── list_utils.c        ← t_token linked list: new, addback, clear, del_one
│   │   └── syntax_error.c      ← check_consecutives, check_if_var
│   └── libft/                  ← 42 standard library
└── readline.supp               ← Valgrind suppressions for readline leaks
```

---

## 🔄 Complete Execution Flow

```mermaid
flowchart TD
    A["main(ac, av, envp)"] --> B["shell_init(envp, &shell)"]
    B --> B1["env_init(envp) → t_env linked list"]
    B --> B2["last_status = 0"]
    B --> C["main2(&shell, envp) — REPL Loop"]
    
    C --> D["interactive_signals()"]
    D --> E["readline('minishell> ')"]
    E -->|NULL / Ctrl+D| Z["ruin_everything(&shell)\nexit(last_status)"]
    E -->|input received| F["add_history(input)"]
    
    F --> G["prepare_for_execution(input, envp, last_status)"]
    
    subgraph PARSING ["🔍 PARSING PIPELINE"]
        G --> G1["tokenization(input)"]
        G1 --> G2["check_if_var(&tokens)\n+ check_consecutives()"]
        G2 --> G3["expand_tokens(&tokens, env, last_status)"]
        G3 --> G4["parsing(tokens)"]
        G4 --> G5["tokenlistclear(&tokens)"]
    end
    
    G5 --> H{"shell->cmds\nnot NULL?"}
    H -->|No| I["free(input)\nloop back"]
    H -->|Yes| J["execution(shell)"]
    
    subgraph EXECUTION ["⚡ EXECUTION ENGINE"]
        J --> J1["init_vals(shell, cmds)\n• check_cmds → set cmd_type\n• fd_in=0, fd_out=1\n• count commands"]
        J1 --> J2{"cmds_count\n== 1?"}
        J2 -->|Yes| K["execute_one_cmd()"]
        J2 -->|No| L["multiple_cmds()"]
    end
    
    J --> M["free_cmds_list(&shell->cmds)"]
    M --> I
    I --> D

    style PARSING fill:#1a1a2e,stroke:#e94560,color:#fff
    style EXECUTION fill:#1a1a2e,stroke:#0f3460,color:#fff
```

---

## 🔍 Tokenization Detail

```mermaid
flowchart LR
    A["Raw Input String"] --> B["tokenization()"]
    B --> C{"For each char"}
    C --> D["set_status()\nTrack quote state:\nDEFAULT / SQUOTE / DQUOTE"]
    D --> E{"In DEFAULT\nstate?"}
    E -->|Yes| F["save_word_or_op()"]
    F --> G{"is_operator()?"}
    G -->|SPACES| H["Flush word, skip"]
    G -->|PIPE| I["Flush word + save '|' token"]
    G -->|< > << >>| J["Flush word + save redir token"]
    G -->|Not operator| K["Continue building word"]
    E -->|No| K
    
    B --> L["check_if_var()\nvariable_check() marks $-containing tokens as VAR"]
    L --> M["check_consecutives()\nValidate syntax: no || >> >> etc."]
    
    style A fill:#16213e,stroke:#e94560,color:#fff
    style B fill:#0f3460,stroke:#e94560,color:#fff
```

**Token Types:** `WORD` | `PIPE` | `INPUT(<)` | `TRUNC(>)` | `APPEND(>>)` | `HEREDOC(<<)` | `SPACES` | `VAR` | `END`

---

## 🧬 Expansion Detail

```mermaid
flowchart TD
    A["expand_tokens()"] --> B["For each token"]
    B --> C{"Token before\nis HEREDOC?"}
    C -->|Yes| D["Skip — don't expand\nheredoc delimiter"]
    C -->|No| E["expand_value(token->value, env, last_status)"]
    
    E --> F{"Character\nanalysis loop"}
    F -->|"$? found"| G["ft_itoa(last_status)\n→ append to result"]
    F -->|"$VAR found"| H["get_env_value(name, env)\n→ append to result"]
    F -->|"$ in single quotes"| I["Keep literal $"]
    F -->|"Regular char"| J["append_char()"]
    
    E --> K{"Contains spaces\n&& not quoted?"}
    K -->|Yes| L["ft_split → word splitting\ncreate_tokens_from_words()\ninsert_list() replaces original token"]
    K -->|No| M["Replace token value\nwith expanded string"]
    
    style A fill:#1a1a2e,stroke:#e94560,color:#fff
```

> [!IMPORTANT]
> **Expansion Rules for Evaluation:**
> - `$VAR` expands in double quotes and unquoted
> - `$VAR` does NOT expand in single quotes  
> - `$?` expands to last exit status
> - Unquoted expansion with spaces triggers **word splitting**
> - Heredoc delimiter is NOT expanded; heredoc **content** IS expanded (unless delimiter was quoted)

---

## ⚡ Single Command Execution

```mermaid
flowchart TD
    A["execute_one_cmd(shell, node)"] --> B["redir_handle(shell, redir, &node)"]
    B --> B1["Walk redir linked list"]
    B1 --> B2{"Type?"}
    B2 -->|"INPUT (<)"| B3["open(filename, O_RDONLY)\n→ node->fd_in"]
    B2 -->|"TRUNC (>)"| B4["open(filename, O_WRONLY|O_TRUNC|O_CREAT)\n→ node->fd_out"]
    B2 -->|"APPEND (>>)"| B5["open(filename, O_WRONLY|O_APPEND|O_CREAT)\n→ node->fd_out"]
    B2 -->|"HEREDOC (<<)"| B6["heredoc() → pipe + readline loop\n→ node->fd_in = fd[0]"]
    
    B --> C{"node still\nalive?"}
    C -->|"No (error freed it)"| D["last_status = 1\nreturn"]
    C -->|Yes| E{"cmd_type?"}
    E -->|NONE| F["execute_non_builtin()"]
    E -->|"Builtin"| G["exec_builtin()"]
    
    F --> F1["fork()"]
    F1 -->|"Child (pid=0)"| F2["default_signals()\ndup2 fd_in→0, fd_out→1\nexecute() → execve"]
    F1 -->|Parent| F3["ignore_signals()\ncheck_fds(node)\nwait_child()"]
    
    G --> G1{"Which builtin?"}
    G1 -->|echo| G2["e_echo() — handle -n flags"]
    G1 -->|cd| G3["e_cd() — chdir + update PWD/OLDPWD"]
    G1 -->|pwd| G4["e_pwd() — getcwd or fallback to env PWD"]
    G1 -->|export| G5["e_export() — print sorted env (stub for assign)"]
    G1 -->|unset| G6["e_unset() — remove from env (stub)"]
    G1 -->|env| G7["e_env() — print all env key=value"]
    G1 -->|exit| G8["e_exit() — validate args, ruin_everything, exit()"]

    style A fill:#0f3460,stroke:#e94560,color:#fff
    style F fill:#16213e,stroke:#0f3460,color:#fff
    style G fill:#16213e,stroke:#e94560,color:#fff
```

---

## 🔗 Pipeline Execution (multiple_cmds)

```mermaid
flowchart TD
    A["multiple_cmds(shell, cmds)"] --> A0["ignore_signals()\nprev_fd = -1"]
    A0 --> B["LOOP: while cmds"]
    
    B --> C["mcc(shell, &cmds, prev_fd)"]
    C --> C1{"Has next cmd?"}
    C1 -->|Yes| C2["pipe(shell->fd)"]
    C1 -->|No| C3["No pipe needed"]
    
    C --> C4["redir_handle() — apply redirections"]
    C --> C5["Wire prev_fd → fd_in\nWire pipe write → fd_out"]
    
    B --> D["fork()"]
    D -->|"Child"| E["run_pipeline(shell, node)"]
    E --> E1["default_signals()"]
    E1 --> E2["dup2(fd_in, 0)\ndup2(fd_out, 1)"]
    E2 --> E3["Close unused pipe end:\nif next cmd → close(fd[0])"]
    E3 --> E4{"Builtin?"}
    E4 -->|No| E5["execute() → execve"]
    E4 -->|Yes| E6["exec_builtin()\nexit(last_status)"]
    
    D -->|Parent| F["check_fds(node)\nprev_fd = fd[0] or -1"]
    F --> G["cmds = cmds->next"]
    G --> B
    
    B -->|"Loop done"| H["Close remaining prev_fd\nwait_all() — waitpid for every fork_id > 0"]
    
    style A fill:#0f3460,stroke:#e94560,color:#fff
    style E fill:#16213e,stroke:#e94560,color:#fff
```

---

## 📡 Signal Handling

```mermaid
flowchart LR
    subgraph Interactive ["Interactive Mode (readline)"]
        A["SIGINT → sigint_interactive()\n• g_sig = 130\n• write newline\n• rl_on_new_line + rl_replace_line + rl_redisplay"]
        B["SIGQUIT → SIG_IGN"]
    end
    
    subgraph Ignore ["Parent During Execution"]
        C["SIGINT → SIG_IGN"]
        D["SIGQUIT → SIG_IGN"]
    end
    
    subgraph Child ["Child Process"]
        E["SIGINT → SIG_DFL"]
        F["SIGQUIT → SIG_DFL"]
    end
    
    subgraph Heredoc ["Heredoc Mode"]
        G["SIGINT → her_int()\n• g_sig = 130\n• close(STDIN)\n• print newline"]
        H["SIGQUIT → SIG_IGN"]
    end

    style Interactive fill:#1a1a2e,stroke:#e94560,color:#fff
    style Ignore fill:#1a1a2e,stroke:#0f3460,color:#fff
    style Child fill:#1a1a2e,stroke:#16213e,color:#fff
    style Heredoc fill:#1a1a2e,stroke:#533483,color:#fff
```

---

## 🧹 Memory Management Flow

```mermaid
flowchart TD
    A["Each REPL iteration"] --> B["prepare_for_execution()"]
    B --> B1["tokenlistclear() — free all tokens"]
    B --> B2["Returns t_cmd* list"]
    
    A --> C["After execution()"]
    C --> C1["free_cmds_list(&shell->cmds)"]
    C1 --> C2["free_current_cmd() per node:\n• check_fds() — close fd_in/fd_out > 2\n• free2d_array(args)\n• free redir chain (filename + node)\n• free(cmd node)"]
    
    A --> D["free(input) — readline buffer"]
    
    E["On exit / Ctrl+D"] --> F["ruin_everything(shell)"]
    F --> F1["env_ruin() — free all t_env nodes"]
    F --> F2["free_cmds_list() — if any remaining"]

    style A fill:#1a1a2e,stroke:#e94560,color:#fff
    style E fill:#1a1a2e,stroke:#e94560,color:#fff
```

---

## 🗂️ Core Data Structures

### `t_exec` — Shell State
| Field | Type | Purpose |
|-------|------|---------|
| `envp` | `char**` | Raw env array (passed from main) |
| `cmds_count` | `int` | Number of commands in current line |
| `fd[2]` | `int[2]` | Current pipe file descriptors |
| `last_status` | `int` | `$?` — last exit status |
| `first_env_node` | `t_env*` | Env linked list head |
| `sorted_env` | `t_env*` | Sorted env for `export` display |
| `cmds` | `t_cmd*` | Current command list head |

### `t_cmd` — Single Command Node
| Field | Type | Purpose |
|-------|------|---------|
| `fork_id` | `int` | PID from fork() or 0 |
| `ret_stat` | `int` | Return status (unused directly) |
| `fd_in` | `int` | Input FD (0=stdin, or pipe/redir) |
| `fd_out` | `int` | Output FD (1=stdout, or pipe/redir) |
| `args` | `char**` | NULL-terminated argument array |
| `cmd_type` | `t_cmd_type` | NONE/ECHO/CD/PWD/EXPORT/UNSET/ENV/EXIT |
| `redir` | `t_redir*` | Redirection linked list |
| `next` | `t_cmd*` | Next command in pipeline |

### `t_redir` — Redirection Node
| Field | Type | Purpose |
|-------|------|---------|
| `filename` | `char*` | Target file or heredoc delimiter |
| `quoted` | `int` | Was delimiter quoted? (heredoc: no expansion) |
| `type` | `t_token_type` | INPUT/TRUNC/APPEND/HEREDOC |
| `next` | `t_redir*` | Next redirection |

### `t_token` — Lexer Token
| Field | Type | Purpose |
|-------|------|---------|
| `value` | `char*` | Token string |
| `type` | `t_token_type` | WORD/PIPE/INPUT/TRUNC/APPEND/HEREDOC/VAR/END |
| `quoted` | `int` | Contains quotes (affects word splitting) |
| `prev/next` | `t_token*` | Doubly-linked list pointers |

---

## 🎯 Evaluation Checklist — Quick Reference

### Things That Work ✅
- [x] echo with/without -n, -nnnnn, mixed flags
- [x] pwd (with getcwd fallback)
- [x] cd (HOME, absolute, relative, .., error cases)
- [x] env (prints KEY=VALUE)
- [x] exit (numeric, non-numeric, too many args, wrapping)
- [x] $VAR expansion in double quotes and unquoted
- [x] $VAR NOT expanded in single quotes
- [x] $? expansion
- [x] Pipes (multi-stage pipelines)
- [x] Redirections: >, >>, <
- [x] Heredoc with expansion and quoted delimiter
- [x] Signal handling: Ctrl+C in interactive/execution/heredoc
- [x] Ctrl+D exits cleanly
- [x] Ctrl+\ ignored in interactive mode

### Known Limitations / Watch During Eval ⚠️
- [ ] `export` with arguments — **STUB** (no `export KEY=VALUE` implementation)
- [ ] `unset` — **STUB** (loop body is empty, doesn't actually remove vars)
- [ ] `export` display doesn't sort alphabetically
- [ ] `envp` is the **original** `char**` from `main()` — not rebuilt after export/unset changes
- [ ] `error_display()` hardcodes `last_status = 2` — may cause wrong exit codes
- [ ] Heredoc SIGINT: closes STDIN_FILENO directly (risky, but restored via `dup`)
- [ ] `e_exit` writes "exit\n" to stderr even when `node->next` exists in a pipeline? (line 73 checks `!node->next`)
- [ ] No support for `||`, `&&`, `()`, wildcards (not required by subject)

### File Descriptor Safety Points 🔒
1. **Pipe FDs**: Created in `mcc()`, read-end carried as `prev_fd`, write-end assigned to `fd_out`
2. **Redir FDs**: Old FD closed if > 2 before assigning new one
3. **Heredoc FD**: `pipe()` created, write-end closed after loop, read-end becomes `fd_in`
4. **check_fds()**: Closes `fd_in`/`fd_out` if > 2, resets to 0/1
5. **apply_fd()**: `dup2() + close()` — standard pattern
6. **Potential leak**: If `pipe()` fails in `mcc()`, `fork_id` set to -1 but `prev_fd` might not be closed

---

## 🏗️ How Input Flows Through the System

```
User types: echo "hello $USER" | cat > out.txt

Step 1 — TOKENIZE:
  [echo] [WORD] → ["hello $USER"] [WORD,quoted] → [|] [PIPE] → [cat] [WORD] → [>] [TRUNC] → [out.txt] [WORD]

Step 2 — SYNTAX CHECK:
  check_if_var() → marks "$USER" token as VAR type
  check_consecutives() → validates no invalid sequences

Step 3 — EXPAND:
  "hello $USER" → "hello moabed" (expands $USER, keeps quotes removed)

Step 4 — PARSE → t_cmd linked list:
  CMD1: args=["echo", "hello moabed"], redir=NULL, next→CMD2
  CMD2: args=["cat"], redir→{type=TRUNC, filename="out.txt"}, next=NULL

Step 5 — EXECUTE (cmds_count=2 → multiple_cmds):
  pipe(fd)
  CMD1: fd_in=0, fd_out=fd[1] → fork → execve("echo", ...)
  CMD2: fd_in=fd[0], fd_out=open("out.txt") → fork → execve("cat", ...)
  wait_all()
```
