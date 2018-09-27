# Let's Implement: Basic Linux Commands in C

C implementation of basic linux commands like ls, mv, cp, grep...

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
```
ls
```

The output (executable) of the commands are located in repo/binaries/$(command_name)/$(command_name)
