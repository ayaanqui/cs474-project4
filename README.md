## Instructions
This program uses the g++ compiler to run the program. On Linux or Mac you can run the `make build` command to build binary file which should be name `program` or `program.out` on Windows. You can either run the binary by running `./program` or by running `make run`.

### Linux/Mac
```
$ make build; make run
```

### Windows
```
> g++ -O2 -std=c++11 -Wall main.cpp expression/Expression.cpp variable_snapshot/VariableSnapshot.cpp Program.cpp Instruction.cpp -o program
> ./program.out
```

### Testing memory leaks with Valgrind
`make valgrind` takes the existing binary and analyses memeory allocations and possible leaks.
```
$ make build; make valgrind
```