## 42-Minishell

1) Terminal vs. Bash vs. Command line vs. Prompt

Terminal or (terminal emulator) : is the windows which pops up to your screen 

BASH : which is the language runs inside this window or ZSH,
to see which language running run : echo $(0)

So , the command line is where you interact with the language itself 

every language installed like BASH will look over a configuration file to be set , of

these confs is the prompt that pops up in each time you try to enter a command

which can be changed using PS1=" example" .

2) BASH Environment | Aliases, Functions and Scripts

Shell is one step above kernel , it became a universal language that runs on almos every OS either linux , mac or windows

you can use BASH to communicate with the computer using human readable commands

environmental variables are configurations stored in memory for system purposes

confuguration in ex. BASH are in the .bashrc file , the plcae where you can create things like:

aliases : using alias alias_name="the_command"

function: using function_name() {the function content}

3) Shell program explained

shell is the user mode program that implements the CLI 

1) it prints a prompt
2) read a line 
3) parse input
4) execute

built on xv6 kernel architecture (MIT edu version) , with versions like x86 and RISC-V

things shell can do:

run a program with option (- flags , etc..)
I/O redirection for stdin and stdout 
pipe the output to input other command or program
sequencing the programs run using ;
run the program in background using &
use parentheses () in commands

xv6 comes with 20 systemcalls

fork exec exit wait : for process control

open close read write : for I/O

chdir : to change dir

when a command is prompted to shell , it builds a tree representation 

#### functions behavior 

1) readline(): reads a line from standard input , similiar to GNL and returns it malloc'd in a char *

2) rl_clear_history(): The rl_clear_line() function clears the history list by deleting all of the entries. The rl_clear_line() function frees data that the readline library saves in the histroy list.

3) rl_on_new_line(): The rl_on_new_line() function tells the update routine that we have moved onto a new empty line, usually used after outputting a line.

4) rl_redisplay(): The rl_redisplay() change what's displayed on the screen to reflect the current contents of rl_line_buffer.

5) add_history(): The add_history() function saves the line passed as parameter in the history so it can be retrieved later in the terminal (like pressing the up arrow in bash).

6) rl_replace_line()
<!-- others -->

7) getcwd() : return the current working directory 

8) isatty() : checks if we are on a tty

9) ttyname() : prints the current terminal entry point ex./dev/pts/0

10) 
# include <unistd.h>

int main()
{
    char *s, *buf;
    s = getcwd(NULL,0);
    printf("%s \n",s);
}

8) chdir(): change the current dir to the dir specified in the parameted given,n success, zero is returned.  On error, -1 is returned.

9) 

checklist to be done :
1) pipex with bonus 
2) activate signals for CTRL +C etc..
3) initiate the shell loop 

Signals 

Used to inter-process communication ex. write two programs or in the same program use fork ,
you can make the simulation of process kill by sending a kill message to other process

there is a list of predefine signals ,two of them , SIGUSR1 , SIGUSR2 are used freely by the user to define the type of signal wanted to be sent

interrupt != terminate

each signal has a default handler ex. terminate in SIGUSR1 unless we change the behavior of it

CTRL + C SIGINT : used to catch this keybind
CTRL + D (SIGQUIT) : 
CTRL + \ EOF : end of file

## pipes

to create a pipe just use pipe(fd)

then use fork , in the order the file descriptors will be copied over 
that means if you close the file de in the ex. child process they will
remain open in the other process(independent from each other)

## redir
cat  > out.txt to redirect the output to outfile
cat < infile OR < file cat  to take an input from a file 

## Unix notes
/dev/pts : this filesystem has nothing stored in it , it lives purely on memory.

terminals can be either a hardware terminals (tty) or pseudo-terminals (pty).

ttys are connected over interface such as serial port (ttyS0) or USB(ttyUSB0)
or over PC screen(tty1).

pty's are provided by terminal emulator which is an application ex of pty : 
sshd , telnet, tmux relay and output from and to another terminal.

experiment: run tty command , take the result ex./dev/pts/0 0 is an entry, in 
another shell command echo hello >/dev/pts/0 , the output is popped on the first terminal.

its easy to pop up an output to different terminals using write function,
if multipe programs tries to read from same termianl each charachter is routed to
different program