*This project has been created as part of the 42 curriculum by samarnah, moabed.*

# Minishell

## Description

Minishell is a simplified Unix shell developed as part of the 42 curriculum.  
The goal of this project is to recreate the behavior of a basic shell while gaining a deeper understanding of:

- process creation and management
- file descriptors and redirections
- pipes
- signals
- environment variables
- parsing and lexical analysis

This shell reads user input, tokenizes and parses commands, expands variables, handles redirections and pipes, and executes commands similarly to Bash.

### Features

Implemented features include:

- Interactive shell prompt
- Command history
- Execution of binaries using `PATH`
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Environment variable expansion (`$VAR`)
- Exit status expansion (`$?`)
- Pipes (`|`)
- Input/output redirections:
  - input redirection `<`
  - output redirection `>`
  - append redirection `>>`
  - heredoc `<<`
- Quote handling:
  - single quotes `'`
  - double quotes `"`
- Signal handling:
  - `Ctrl-C`
  - `Ctrl-D`
  - `Ctrl-\`

---

## Project Structure

```bash
minishell/
├── headers/        # Header files
├── code files/     # Code files .c
├── libft/          # Custom C library
├── Makefile
└── README.md
```

---

## Instructions

### Compilation

Clone the repository and compile using:

```bash
git clone <repository_url>
cd minishell
make
```

This generates the executable:

```bash
./minishell
```

### Available Make Commands

```bash
make        # Compile project
make clean  # Remove object files
make fclean # Remove object files + executable
make re     # Recompile everything
```

---

## Usage

Run minishell:

```bash
./minishell
```

Example commands:

```bash
echo hello world
pwd
ls -la | grep minishell
cat file.txt > output.txt
cat << EOF
hello
EOF
echo $HOME
echo $?
```

Exit shell:

```bash
exit
```

---

## Technical Choices

### Parsing

The parser is responsible for:

- tokenizing input
- syntax validation
- quote management
- operator detection:
  - pipes
  - redirections
  - heredocs

### Expansion

Implemented expansion logic for:

- environment variables
- exit status `$?`

Expansion behavior respects shell quoting rules:
- expansion disabled inside single quotes
- expansion enabled inside double quotes

### Execution

Execution pipeline handles:

- built-ins in parent process when required
- external commands using `fork()` + `execve()`
- pipes with `dup2()`
- redirections using file descriptors

### Memory Management

Special care was taken to:

- free allocated memory
- avoid leaks during parsing and execution
- handle shell exit cleanup properly

---

## Resources

### Documentation & References

- Bash Reference Manual  
  https://www.gnu.org/software/bash/manual/

- Linux man pages  
  https://man7.org/linux/man-pages/
  
- Building shell in C videos
  https://www.youtube.com/playlist?list=PL6F3pyVdiAketRFfDowXEGEU15omtI36J

- 42 Minishell subject

### Helpful Tutorials

- Pipes, forks, and exec:
  https://beej.us/guide/bgipc/

- Signals in C:
  https://man7.org/linux/man-pages/man7/signal.7.html

---

## AI Usage

AI tools were used as supplementary resources during development.

Used for:
- debugging linker/compiler errors
- understanding Bash edge cases
- testing command behavior and dangerous edge cases
- brainstorming test cases

---

## Authors

- samarnah
- moabed