## Ram Machine Simulator
__This is a program in C++ to simulate Ram Machine on Linux__.

It consists on three parts:
* Input tape
* Output tape
* Memory
* Program

To compile the __Ram Machine__ open a *terminal* and put

`> make`

It will compile all necessary files and create an executable (__RamMachine__). To execute correctly the Ram Machine you must indicates four parameters:
+ [input]
 - Indicates the file name of the input tape.
+ [output]
 - Indicates the file name of the output tape.
+ [program]
 - Indicates the file name of the ram program (like assembly language)
+ [size]
 - Number of registers that will have the memory

Example:

`> /RamMachine input1.txt output.txt test1.ram 5`

This example will use *input1.txt* as input, create *output.txt* if it doesn't exists to write in, use *test1.ram* to decide what to do with the input data to output the result and it will create a memory with 5 registers.
