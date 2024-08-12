# ABM - A Boring Machine

ABM is a stack-based virtual machine with an interpreted assembly-like source code syntax.
This was just a personal project to learn and experiment, and is not suited for any real-world
use. As a result, ABM is not turing-complete. You are welcome to try it out though.

Example ABM source (calculates and prints the factorial of 7):
```
lvalue i
push 7
:=

lvalue result
push 1
:=

label loop
    rvalue i
    push 0
    =
    gotrue end

    lvalue result
    rvalue result
    rvalue i
    *
    :=

    lvalue i
    rvalue i
    push 1
    -
    :=
goto loop

label end
rvalue result
print
```
Output:
```
5040
```

## Building

ABM doesn't have any dependencies and a very simple build process. Therefore, no build tools is used.
To bulid from source, clone this repository, `cd` into `src`, and run:
```bash
# *nix:
gcc -I. -o main *.c **/*.c
# Windows
gcc -I. -o main.exe *.c **/*.c
```
This will create an executable named `main` (or `main.exe`) in the directory.

## Usage & Source Code

The ABM binary takes a single argument, an ABM source file. Providing no argument displays a short
usage. The file can be named anything and the extension doesn't matter, even though the provided
samples use the extension `.abm`.

The ABM source code resembles assembly code, but technically is higher level that assembly. Therefore,
it is more appropriate to call it an interpreted language that just resembles assembly code.

Each line in an ABM source file contains an instruction and the argument to that instruction (if any),
seperated by the first space. The lines are trimmed when being parsed, allowing the code to be indented
as needed. Empty lines (and lines containing only whitespace) are skipped. Comments are not supported.

The full instruction set for ABM can be found [in the ISA](docs/isa.md).

## Samples

Some samples are included in the repository in `samples`. The `.abm` files contain the sources and the
corresponding `.output` files contain their outputs.
