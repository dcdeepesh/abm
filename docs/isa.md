# ABM Instruction Set Architecture

Each section contains the syntax of the respective instruction,
a description, and for most of them, an example. The section on
operators in an exception, they've been condensed together due to
very similar usage.

The stack in the examples is represented from bottom to top.

ABM doesn't support comments in its source code,
but double slash comments are used here for explanation.

## Stack Controls

These instructions control putting data on, and removing data from, the stack.

### 1. `push`
```
push <value>
```
Pushes a number to the top of the stack.
```
push 6
push 7
push -5
// Stack: 6, 7, -5
```

### 2. `pop`
```
pop
```
Removes the value at the top of the stack.
```
// Stack: 6, 5, 10
pop
// Stack: 6, 5
pop
// Stack: 6
```

### 3. `copy`
```
copy
```
Pushes a copy of the top value onto the stack.
```
push 10
push 6
copy
// Stack: 10, 6, 6
copy
// Stack: 10, 6, 6, 6
```

### 4. `lvalue`
```
lvalue <identifier>
```
Puts the "lvalue" of an identifier on the stack. Used to prepare for an assignment.
Read the section on `:=` to learn more.
If the identifier doesn't exist, it is created with the value 0.
In the examples, lvalues are shown on the stack by their identifiers.
```
push 5
lvalue a
// Stack: 5, a
```

### 5. `:=` (assign)
```
:=
```
Assigns the value at the top of the stack to the identifier at (top - 1) of the stack, and pops both.
```
lvalue a
push 10
// Stack: a, 10
:=
// The value of a is now 10. Stack is empty.
```

### 6. `rvalue`
```
rvalue <identifier>
```
Pushes the value of an identifier to the top of the stack.
```
lvalue myVariable
push 55
:=
// myVariable := 55. Stack is empty.

push 10
rvalue myVariable
// Stack: 10, 55
```

## Printing Stuff

These instructions are used to display data to the terminal.

### 1. `show`
```
show <string>
```
Prints a string to the terminal.
```
show Hello World!
// "Hello World!" is printed to the terminal.
```

### 2. `print`
```
print
```
Prints the value at the top of the stack to the terminal.
```
// Stack: 4, 5, 6
print
// "6" is printed to the terminal. Stack remains the same.
```

## Operators

Operator instructions pop their operand(s) from the stack, do some operation, and push the result back onto the stack.
The operands must pushed to the stack left-to-right, and then the operator should be used.
Operator instructions don't have any arguments, they're used as-is on their own line.

As a simple example:
```
push 4
push 9
+
// Stack: 13
// (can be thought of as "4 + 9")

// Assuming length = 4, breadth = 7
rvalue length
rvalue breadth
*
// Stack: 28
// can be thought of as "length * breadth")
```

The following sub-sections assume `op1`, `op2`, ... are the operands required by the operator in question,
pushed onto the stack in that order, left-to-right.
As a result, you can think of the operations as:
- For unary operators: `result = <operator> op1`
- For binary operators: `result = op1 <operator> op2`
So, for example:
```
rvalue a
!
// basically means "!a"

rvalue val1
rvalue val2
*
// basically means "val1 * val2"
```

The explanations below also show a corresponding C-like syntax for the operators in parantheses.

### Arithmetic Operators
- `+`: Adds the operands (`op1 + op2`).
- `-`: Subtracts the right operand from the left operand (`op1 - op2`).
- `*`: Multiplies the operands (`op1 * op2`).
- `/`: Performs an integer division. The result is the quotient after dividing `op1` by `op2` (`(int) (op1 / op2)`).
- `div`: Perorms a modulo. The result is the remainder after dividing `op1` by `op2` (`op1 % op2`).

### Relational Operators
Relational operators produce a boolean result, with `1` representing `true` and `0` representing `false`.
- `=`: Tests for equality (`op1 == op2`)
- `<>`: Tests for inquality (`op1 != op2`)
- `<`: Tests if the left operand is less than the right (`op1 < op2`)
- `<=`: Tests if the left operand is less than or equal to the right (`op1 <= op2`)
- `>`: Tests if the left operand is greater than the right (`op1 > op2`)
- `>=`: Tests if the left operand is greater than or equal to the right (`op1 >= op2`)

### Logical Operators
These operators treat their integer operands as boolean values, where `0` represents `false` and everything else `true`.
- `&`: Performs a logical AND (`op1 & op2`).
- `|`: Performs a logical OR (`op1 | op2`).
- `!`: Unary operator. Performs a logical negation. Emits `1` for `true` (`!op1`).

## Control Flow

Control flow instructions allow primitive branching. This branching can also be used to implement loops.

### 1. `label`
```
label <identifier>
```
Defines a label. A label is a point in source code that can be jumped to.
All the labels in a source file are processed in the first pass of the interpreter,
so you can jump to any label whether it's defined before or after a jump.
Because the label instruction itself doesn't do anything, jumping to a label effectively
starts execution of the instructions after that label.
```
label beginning
```

### 2. `goto`
```
goto <identifier>
```
Jumps to a label, unconditionally.
```
label hello
show Hello World!
goto hello

// Prints "Hello World!" forever.
```

### 3. `gotrue`
```
gotrue <identifier>
```
Jumps to a label if the top of the stack is true (non-zero), while also popping it.
```
// Stack: 4, 2
gotrue second
label first
show This won't be printed
label second
show This will be printed
// Stack: 4
```

### 4. `gofalse`
```
gofalse <identifier>
```
Jumps to a label if the top of the stack is false (zero), while also popping it.
```
// Stack: 4, 0
gofalse second
label first
show This won't be printed
label second
show This will be printed
// Stack: 4
```

### 5. `halt`
```
halt
```
Halts the machine. This is one of the only two ways to correctly quit from an ABM program.
The other is when the interpreter reaches the end of a file, meaning there are no more instructions to execute.
As a result, each ABM source file containing procedures will have at least one `halt` instruction
(because procedures need to be defined after the "main" code),
unless it wants to loop forever. In such cases, the machine needs to be stopped externally,
e.g. by nterrupting the program (Ctrl+C), sending a kill signal, etc.

## Procedures

ABM has basic support for procedures. Procedures are blocks of instructions that may be reused,
accept arguments, and return values (indirectly). Because a procedure is still just a sequence
of instructions, it'll be executed if the interpreter runs into it.
Therefore, to ensure correct behaviour, all procedures must be defined after the "main" block of code
in the beginning, ending with the `halt` instruction. Resulting in code looking somewhat like this:
```
// "main" block of instructions.
halt

// procedure 1

// procedure 2

// ...
```
This makes sure the interpreter will run the "main" code, occasionally calling and return from
the procedures, and ending with a `halt`, never running into the procedure code unless instructed to.

A procedure is just a block of instructions beginning with a `label` and ending with a `return`.
Counterintuitively, `begin` and `end` are not used to define a procedure, but instead the calling
of a procedure, which means everything inside a `begin` and an `end` is used to prepare arguments,
call the procedure, and handle return values. The overall code looks like this:
```
// ... "main" code
begin
    // prepare arguments (if any)
    call myProcedure
    // handle return values (if any)
end
// ... more "main" code

label myProcedure
    // ... procedure code
return
```

### Calling Convention, 1. `begin`, and 2. `end`
The `begin` and `end` instructions mark the beginning and ending of a block of instructions that:
1. Prepare arguments for a procedure call
2. Call the procedure
3. Handle return values from the procedure

Arguments and return values may or may not present. In the case that neither of them are present
and the only thing needed to call the procedure is a `call`, the `begin`-`end` block (aka BE block)
may be skipped. The only purpose of the block is to prepare the machine to handle variables being
passed to and from the procedure. If there aren't any variables, the block isn't needed, and the
procedure call (`call`) essentially becomes a `goto`, jumping the machine to the procedure and
returning back to the jump due to the `return` in the procedure code. If a BE block is
added in such a situation, it doesn't have any effect. Such code looks like this:
```
show First
call foo
show Third

label foo
    show Second
return
```

#### Arguments
When arguments are present, they are shared between the caller's BE block and the callee's procedure body.
When any new variable is created (using `lvalue`) inside a BE block, that varible is shared, by name,
to the callee. The callee, in its procedure body, may use the variable
as if it's defined locally. In the caller, the variable's scope is limited to the BE block. When the
`end` instruction is encountered, the shared variable (the argument) is destroyed.

Note that this means that the variable names are shared between the callee and the caller('s BE).
If a procedure expects variables `a` and `b`, the caller needs to create those variables in it's
BE block before calling that procedure.

```
begin
    lvalue arg1
    rvalue 14
    :=
    lvalue arg2
    rvaule 78
    :=
    call foo
end
halt

label foo
    print arg1
    print arg2
return

// Output:
// 14
// 78
```

#### Return Values
When a procedure creates a variable inside its body, that variable is shared between that procedure's body
and the caller's (if any) BE block (if any). When the procedure returns, the caller can access those variables
using their names for the rest of its BE block. This allows the procedure to return values back to the caller.
Note that this means that the callee doesn't have any "private" variables, as all of them are shared with the caller,
and that this also means that a callee can "return" multiple values.
```
begin
    call getFive
    rvalue ret
    print
end
halt

label getFive
    lvalue ret
    rvalue 5
    :=
return

// Output:
// 5
```

### 3. `call`
```
call <ientifier>
```
Calls a procedure. If the call occurs in a BE block, any arguments and/or return values are handled as mentioned
previously.

### 4. `return`
```
return
```
Returns back to the caller. Therefore, also marks the end of a procedure.
