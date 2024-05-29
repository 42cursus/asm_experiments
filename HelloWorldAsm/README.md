### How can I examine contents of a data section of an ELF file on Linux?
* https://stackoverflow.com/questions/1685483


    You can get the RAW (not hexdump-ed) ELF section with:
        # To a file:
        objcopy ../bin/strlen /dev/null --dump-section .data=data.txt
        # To stdout:
        objcopy ./hw1 /dev/null --dump-section .data=/dev/stdout | cat
    
    objdump -d -Mintel64,addr64 main -j .text
    objdump -d -Mintel-mnemonic hw1 -j .data  -m i386:x86-64:intel
    objdump -mi386 strlen -Mintel64,addr64 -d -j .text

###  Does libc have a main() in there somewhere?

* https://www.reddit.com/r/C_Programming/comments/15mjopz/comment/jvgvjfe/

#### A little bit of an interrogation:

We can interrogate a binary with ldd to find the system libc:

    $ ldd /bin/ls | grep libc
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f2c29b0d000)

Every ELF header has an entry point, even in shared libraries. 
In fact, on modern systems nearly all your system programs are shared objects
because that's how Position Independent Executables (PIE) are implemented.
readelf will display lots of information about ELF files,
including this entry point:

    $ readelf -a /lib/x86_64-linux-gnu/libc.so.6 | grep Entry
        Entry point address:               0x23e40

There's also an "interpreter":

    $ readelf -a /lib/x86_64-linux-gnu/libc.so.6 | grep -A2 INTERP
        INTERP         0x000000000019f650 0x000000000019f650 0x000000000019f650
        0x000000000000001c 0x000000000000001c  R      0x10
        [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]

That's the dynamic linker, /lib64/ld-linux-x86-64.so.2, which is what's actually
run.\
Its job is to load and link the program, then jump to its entry point.\
If we "run" libc with GDB, and use `starti` to stop at the first instruction: 

    $ gdb /lib/x86_64-linux-gnu/libc.so.6
    Reading symbols from /lib/x86_64-linux-gnu/libc.so.6...
    Reading symbols from /usr/lib/debug/.build-id/e1/5ec78d51a522023f9cfc58dc284f379d81860b.debug...
    (gdb) starti
    Starting program: /lib/x86_64-linux-gnu/libc.so.6
    Program stopped.
    0x00007ffff7fd3090 in _start () from /lib64/ld-linux-x86-64.so.2
    (gdb) disas
    Dump of assembler code for function _start:
    => 0x00007ffff7fd3090 <+0>:     mov    %rsp,%rdi
    0x00007ffff7fd3093 <+3>:     call   0x7ffff7fd3de0 <_dl_start>
    End of assembler dump.

Wounding up inside the dynamic linker. If we follow that call into _dl_start we
end up inside __libc_main inside libc.so:

    (gdb) ni
    0x00007ffff7fd3093 in _start () from /lib64/ld-linux-x86-64.so.2
    (gdb) s
    __libc_main () at version.c:71
    71      version.c: No such file or directory.

That symbol is not listed in libc.so but installing the package `libc6-dbg`,
which has detached debugging symbols \
for GNU C Library, we can further inspect: 

    (gdb) disas
    Dump of assembler code for function __libc_main:
    => 0x0000555555577e40 <+0>:     mov    $0x1,%edi
    0x0000555555577e45 <+5>:     sub    $0x8,%rsp
    0x0000555555577e49 <+9>:     mov    $0x1aa,%edx
    0x0000555555577e4e <+14>:    lea    0x174e2b(%rip),%rsi        # 0x5555556ecc80 <banner>
    0x0000555555577e55 <+21>:    call   0x55555563f460 <__GI___libc_write>
    0x0000555555577e5a <+26>:    xor    %edi,%edi
    0x0000555555577e5c <+28>:    call   0x55555561bbb0 <__GI__exit>
    End of assembler dump.

It's printing out some string. The string is stored in rsi and passed to write(2).
If skip ahead to that instruction, then have a look:

    (gdb) ni 4
    0x0000555555577e55      45      in version.c
    (gdb) p (char *)$rsi
    $1 = 0x5555556ecc80 <banner> "GNU C Library (Debian GLIBC 2.31-13+deb11u6) stable release version 2.31.\nCopyright (C) 2020 Free Software Foundation, Inc.\nThis is free software; see the source for copying conditions.\nThere is NO wa"...


There's the banner it prints, so we are kinda on track.
In a normal C program the entry point is a bit of libc statically linked into
your program.\
It does initialization then calls your program's main.



When the GNU linker doesn't have anything useful to pick for an entry point,
it just chooses the address of .text.
That's is unlikely to start with any useful or meaningful instructions.

    $ echo >empty.c
    $ cc -shared -fPIC empty.c
    $ readelf -a a.out | grep Entry
    Entry point address:               0x1040
    $ readelf -a a.out | grep -F .text | head -n1
    [11] .text             PROGBITS         0000000000001040  00001040

You can select an entry point with --entry/-e to the linker. If you have
a symbol that looks like an entry point, like _start, it will pick that.
Check this out:

    #include <syscall.h>
    
    void _start(void)
    {
        asm("syscall" : : "a"(SYS_exit), "D"(123));
    }

This is an entry point immediately exits with status 123. Does it work?

    $ cc -shared -fPIC example.c
    $ ./a.out ; echo $?
    123

GNU ld implicitly picked _start for the entry point:

    $ nm --defined-only a.out | grep _start
    00000000000010f9 T _start
    $ readelf -a a.out | grep Entry
    Entry point address:               0x10f9