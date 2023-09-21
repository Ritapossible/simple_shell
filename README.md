# simple_shell

![shell](https://camo.githubusercontent.com/8888ae74076afce3ac6d78de0bba2c9c2039412ed8f51d33b5e3a61712cf2406/68747470733a2f2f63646e2e73686f706966792e636f6d2f732f66696c65732f312f303230342f343130342f70726f64756374732f32303138303531372d32303138303531372d50313236303631345f363030782e6a70673f763d31353238353036333538)

## Repository Description

**This repository contains the files to simulate a basic Unix Shell with its respective commands. It uses the POSIX API to implement many of the same functionalities of the first Ken Thompson's Shell and It is made to carry out the 0x16. C - Simple Shell project at ALX Africa.**

**The predominantly used calls are read, write, open, execve, exit, fflush, fork, free, malloc, getline, isatty, perror, strtok, wait, and waitpid.**

**This simple shell is a Shell interface written in C programming language that gives to the user a prompt hsh, after it accepts, it executes a user inputted command in a separate process called child process.**


<<<<<<< HEAD
![c](https://camo.githubusercontent.com/4f0a611698513d0e276aa4bf9345ffe9fa05197036105d372e2d88ade23fc135/68747470733a2f2f7365656b6c6f676f2e636f6d2f696d616765732f432f632d70726f6772616d6d696e672d6c616e67756167652d6c6f676f2d394233324430313742312d7365656b6c6f676f2e636f6d2e706e67) 
=======
![c](https://camo.githubusercontent.com/4f0a611698513d0e276aa4bf9345ffe9fa05197036105d372e2d88ade23fc135/68747470733a2f2f7365656b6c6f676f2e636f6d2f696d616765732f432f632d70726f6772616d6d696e672d6c616e67756167652d6c6f676f2d394233324430313742312d7365656b6c6f676f2e636f6d2e706e67)
--- 
>>>>>>> jack

## General. 

* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
* Your shell should not have any memory leaks
* No more than 5 functions per file
* All your header files should be include guarded

## Process Description
1. First, the parent process is created when the user run the program.
2. Then, the isatty() function using STDIN_FILENO file descriptor -fd- to tests if there is an open file descriptor referring to a terminal. If isatty() returns 1, the prompt is showed using write() with STDOUT_FILENO as fd and waits for an input user command line.
3. When the user types a command, getline() function reads an entire line from the stream and strtok() function breaks the inputted command into a sequence of non-empty tokens.
4. Next, it creates a separate child process suing fork() that performs the inputted command. Unless otherwise is specified, the parent process waits for the child to exit before continuing.
5. After tokening the command, execve() function brings and executes it, the it frees all allocated memory with free().
6. Finally, the program returns to main process: prints the prompt, and waits for another user input.
<<<<<<< HEAD

## Flowchart Description (How it Works)

![image](https://github.com/Ritapossible/simple_shell/assets/124313160/c7b4be67-9d5d-4d1b-9867-4e19e7865224)

=======
>>>>>>> jack
