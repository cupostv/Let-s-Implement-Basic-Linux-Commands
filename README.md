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
