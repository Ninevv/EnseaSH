# Ensea in the Shell

## Introduction

This practical work consists of developping a small shell that displays exit codes and execution times of launched
programs.

## Getting started

To test our project, follow these steps : 

1. Make sure your machine can run linux commands, otherwise you may install a linux bash shell adapted to the operating system of your machine.

2. Clone the repository on your machine :

```bash
   git clone  https://github.com/Ninevv/EnseaSH.git
   ```

3. How to start ?
   
   - Run the main file
   - Launch the shell by executing the './main' command

## Project breakdown

We launch our shell from a terminal.

1. We start by displaying a welcome message. We use the write function to charge the message on an output buffer of the size BUFSIZE, a global variable defined as 128.
   
2. To execute a command entered by the user, we use the read function. We get the input buffer typed on the keyboard using the STDIN_FILENO process.
   Instead of using the strlen function to get the size of the command string, we get the length of the input buffer by getting its read function value. Then, we replace the end of line symbol ('\n') by the end of string symbol('\0').
   The command is executed using the execlp function.
   The shell then prints a prompt (enseash %) waiting for a new command. At this level, we exit the shell by closing the terminal .

3. To exit the shell, we compare the input buffer to the 'exit' string using the strcmp function. We can also verify that the <ctrl+d> command has been entered, which is simple here since its length is null. The shell prints a message before exiting.

4. We make a difference between a father process which consists of managing the shell launch, display and exiting, and a child process that read and executes the input commands. The child process is either terminated normally (WIFEXITED(status)=True) or because of a signal (WIFSIGNALED(status)=True). The shell prints a return corresponding to either of the terminations.

5. We display the command execution time by using the call clock_gettime. The timer starts just before the creation of the child process and finishes once it is terminated. The shell displays the return code and the execution time of each command in micro seconds.


## Contributors
This practical work was the result of joined efforts of the contributors : 
- Louis-Mathis Massin ( lmmas )
- Zineb Lahmoudi ( Ninevv )
