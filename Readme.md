# Bash Buddy

`bsb` helps you remember `bash` syntax without having to look it up. Just compile [bsb.c](./bsb.c)  and put it in you `PATH`.

## Usage

To use `bsb`, you need to pass a query enclosed in quotes.
```
bsb "[QUERY]"
```

The query is matched against a set of predefined queries and the corresponding usage example is printed.

## Example

```
bash-3.2$ bsb "command"
Based on your input we guessed your query is about: pipe command
Use: command1 | command2
    Usage: Sends stdout of one command/process to stdin of 
           Note that not all commands read from stdin or write to stdout!
    Example: 
        cat file.txt | grep "pattern"
```
## Query Options

Do `bsb --help` to see all options.

Here are the available query options:
- "variable declaration": how to declare a variable
- "data types - string integer list": different data types in bash
- "strings": how to work with strings
- "arrays": how to work with arrays
- "string interpolation": how to interpolate a string (also called parameter expansion)
- "arithmetic expression": how to perform arithmetic operations
- "sequence": how to create a sequence of numbers
- "test expression": how to test whether a statement is true or false
- "command substitution": how to substitute a command for the output of the command
- "pipe command": how to send the output of one command to the input of the next
- "redirection": how to redirect the output of a command from and to files or commands
- "conditional statements": how to perform conditional execution based on a condition
- "for loop": repeat a block of code multiple times with for
- "while loop": repeat a block of code multiple times with while
- "until loop": repeat a block of code multiple times with until
- "functions": how to define and use functions
- "exit status": how to check the exit status of a command
- "trap": how to catch signals
