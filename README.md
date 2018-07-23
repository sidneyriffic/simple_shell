# Simple Shell

Run a shell designed to mimic sh. Execute commands and interact with the kernel.

simplesh [script files]

## Current features

* Run commands in $PATH
* Environment and local variables
* $? return values, $$ pid
* $# number of args and $0-9 (not a perfect sh mimic currently though)
* Logical operators &&/|| with multi-line continuation
* ; command separator
* ~ expansion to current user's home directory
* unclosed multi-line quote continuation
* \ escaping
* Run script files, as well as commands from standard input


Built-ins:
* help
* exit [status]
* setenv
* unsetenv
* env (listing environment functionality only)
* cd
* alias
* unalias
* history

## Getting started
To use this shell, we want to compile it and move it into a $PATH folder like /usr/local/bin. To compile the program, clone the project, navigate to the directory, and then type:
```
gcc -o simplesh *.c
```
The copy the output file to /usr/local/bin (you may need to add "sudo" to the front of this line):
```
cp simplesh /usr/local/bin
```
After this you should be able to run the shell by typing "simplesh".

## Usage Examples
To start up the shell and run a simple command (in this case pwd), then exit:
```
Username@your-regular-prompt:~$ simplesh
simplesh:/home/username$ pwd
/home/username/
simplesh:/home/username$ exit
Username@your-regular-prompt:~$
```
pwd lists the current working directory, which is displayed in the simplesh terminal prompt. We can also run script files. If we have a script with the following:
```
#!/usr/bin/env simplesh
echo Hello from simple shell!
```
Then execute the script we will see "Hello from simple shell!" in our terminal. We can also use command line arguments for variables. Currently, $0 is always "simplesh", $1 is the script name, and $2 and beyond are the arguments. So if we want the first argument, we would put in $2 like so:
```
#!/usr/bin/env simplesh
echo Hello $2
```
Then if we want to pass in an argument we can do it like so:
```
Username@your-regular-prompt:~$ ./helloscript "simple shell!"
Hello simple shell!
```

## Testing
There is a repository for the test suite at https://github.com/sidneyriffic/shelltest.git. Follow the instructions there, and you'll want the shell target to be /bin/sh (the default location for sh).

## Authors
Sidney Burkett  
Greg Dame
