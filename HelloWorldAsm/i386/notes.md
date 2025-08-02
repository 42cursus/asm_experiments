[Difference between `volatile` and `__volatile__`](https://stackoverflow.com/questions/14204893)


#### Because of -ansi

Although a real `-ansi` program would not use `asm()`, there needs to be a way to include an asm macro in a header even when the program itself is built with -ansi. (With `-ansi`, gcc doesn't include extensions which conflict with strict ISO C, like new keywords.)

A properly namespaced alternative `__asm__` was necessary for asm, which could not be defined by the system in `-ansi` mode. Now, this wasn't strictly necessary with volatile, which has been a keyword for a long time, but perhaps by inertia someone also (and unnecessarily) made a `__volatile__` (reserved system name format) to go with volatile, even if the program had been legal `-ansi` either way.

#### Given that you haven't defined any of the below names:

* `asm` and `volatile` are language keywords. How do you know? They have no underscore before or after them, hence they are keywords in the language.
* `_something_` (one underscore) is a reserved compiler keyword, type, macro, etc.
* `__asm__`, `__volatile__` and `__whatever_else__` (two underscores) are standard library keywords, macros, etc.

### Commonly used constraints.

There are a number of constraints of which only a few are used frequently. We’ll have a look at those constraints.

    Register operand constraint(r)

    When operands are specified using this constraint, they get stored in General Purpose Registers(GPR). Take the following example:

    asm ("movl %%eax, %0\n" :"=r"(myval));

    Here the variable myval is kept in a register, the value in register eax is copied onto that register, and the value of myval is updated into the memory from this register. When the "r" constraint is specified, gcc may keep the variable in any of the available GPRs. To specify the register, you must directly specify the register names by using specific register constraints. They are:

        +---+--------------------+
        | r |    Register(s)     |
        +---+--------------------+
        | a |   %eax, %ax, %al   |
        | b |   %ebx, %bx, %bl   |
        | c |   %ecx, %cx, %cl   |
        | d |   %edx, %dx, %dl   |
        | S |   %esi, %si        |
        | D |   %edi, %di        |
        +---+--------------------+

    Memory operand constraint(m)

    When the operands are in the memory, any operations performed on them will occur directly in the memory location, as opposed to register constraints, which first store the value in a register to be modified and then write it back to the memory location. But register constraints are usually used only when they are absolutely necessary for an instruction or they significantly speed up the process. Memory constraints can be used most efficiently in cases where a C variable needs to be updated inside "asm" and you really don’t want to use a register to hold its value. For example, the value of idtr is stored in the memory location loc:

    asm("sidt %0\n" : :"m"(loc));

    Matching(Digit) constraints

    In some cases, a single variable may serve as both the input and the output operand. Such cases may be specified in "asm" by using matching constraints.

    asm ("incl %0" :"=a"(var):"0"(var));

    We saw similar examples in operands subsection also. In this example for matching constraints, the register %eax is used as both the input and the output variable. var input is read to %eax and updated %eax is stored in var again after increment. "0" here specifies the same constraint as the 0th output variable. That is, it specifies that the output instance of var should be stored in %eax only. This constraint can be used:

        In cases where input is read from a variable or the variable is modified and modification is written back to the same variable.
        In cases where separate instances of input and output operands are not necessary.

    The most important effect of using matching restraints is that they lead to the efficient use of available registers.

Some other constraints used are:

    "m" : A memory operand is allowed, with any kind of address that the machine supports in general.
    "o" : A memory operand is allowed, but only if the address is offsettable. ie, adding a small offset to the address gives a valid address.
    "V" : A memory operand that is not offsettable. In other words, anything that would fit the `m’ constraint but not the `o’constraint.
    "i" : An immediate integer operand (one with constant value) is allowed. This includes symbolic constants whose values will be known only at assembly time.
    "n" : An immediate integer operand with a known numeric value is allowed. Many systems cannot support assembly-time constants for operands less than a word wide. Constraints for these operands should use ’n’ rather than ’i’.
    "g" : Any register, memory or immediate integer operand is allowed, except for registers that are not general registers.

Following constraints are x86 specific.

    "r" : Register operand constraint, look table given above.
    "q" : Registers a, b, c or d.
    "I" : Constant in range 0 to 31 (for 32-bit shifts).
    "J" : Constant in range 0 to 63 (for 64-bit shifts).
    "K" : 0xff.
    "L" : 0xffff.
    "M" : 0, 1, 2, or 3 (shifts for lea instruction).
    "N" : Constant in range 0 to 255 (for out instruction).
    "f" : Floating point register
    "t" : First (top of stack) floating point register
    "u" : Second floating point register
    "A" : Specifies the `a’ or `d’ registers. This is primarily useful for 64-bit integer values intended to be returned with the `d’ register holding the most significant bits and the `a’ register holding the least significant bits.

### Constraint Modifiers.

While using constraints, for more precise control over the effects of constraints, GCC provides us with constraint modifiers. Mostly used constraint modifiers are

    "=" : Means that this operand is write-only for this instruction; the previous value is discarded and replaced by output data.
    "&" : Means that this operand is an earlyclobber operand, which is modified before the instruction is finished using the input operands. Therefore, this operand may not lie in a register that is used as an input operand or as part of any memory address. An input operand can be tied to an earlyclobber operand if its only use as an input occurs before the early result is written.

    The list and explanation of constraints is by no means complete. Examples can give a better understanding of the use and usage of inline asm. In the next section we’ll see some examples, there we’ll find more about clobber-lists and constraints.

### Some useful commands 

`gcc -S 
    -m32 
    -mmanual-endbr 
    -fPIE
    -fno-pic
    -fcf-protection=none
    -fno-dwarf2-cfi-asm
    -fno-omit-frame-pointer
    -fno-asynchronous-unwind-tables
    -Wa,-alh,-L
    -Wl,-znoexecstack
    -Wl,-znoexecflags
    -O0 main.c`

`nasm -f elf -o hw.o hw.asm`
`ld -m elf_i386 -s -o hw hw.o`