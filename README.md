# Let's Implement: Basic Linux Commands in C

C implementation of basic linux commands like ls, mv, cp, grep... This repository is only
for practice purpose.

## Build

In order to build all commands, type
```
make -s
```
In order to build specific command, type
```
make -s $(command_name)
```
Available commands are:
- ls

The output (executable) of the commands will be generated in $(repo_path)/binaries/$(command_name)/$(command_name)

## LS command demo

ls command shows content of a directory. Image below shows example of running original Linux command ls and custom made ls command from this repository on a home directory.

### Without extra arguments
Figure below shows output example of original linux ls command on a home directory.
<p align="center">
    <i>Figure 1: Output example of original ls command</i>
    <img src="https://i.imgur.com/wFY8NJ4.png" alt="Original ls" width="70%"> 
</p>

Figure below shows output example of custom ls command on a home directory.
<p align="center">
    <i>Figure 2: Output example of custom ls command</i>
    <img src="https://i.imgur.com/ArT1z3W.png" alt="Custom ls" width="70%"> 
</p>
