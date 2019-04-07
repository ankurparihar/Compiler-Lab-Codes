## Problem statement
Imagine the syntax of a programming language construct such as _while-loop_ --
```
while ( condition ) 
begin 
      statement ; 
            : 
end
```

where _while_, _begin_, _end_ are keywords; condition can be a single comparision expression (such as `x == 20`, etc.); and statement is the assignment to a location the result of a single arithmatic operation (eg., `a = 10 * b`).<br>
Write a program that verifies whether the input follows the above syntax. Use flex to create the lexical analyser module and write a C program that performs the required task using that lexical analyser.

## How to run

- Important: `flex` must be installed. To install `flex` run `sudo apt install flex`
- Run: `./script.sh`
- Input: write a simple while loop program in [test.c](./test.c)
- Generates an intermediate file [inter](./inter)