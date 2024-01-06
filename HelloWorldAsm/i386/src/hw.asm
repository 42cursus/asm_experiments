BITS 32

section .text                   ;section declaration
                                ;we must export the entry point to the ELF linker or
    global  _start              ;loader. They conventionally recognize _start as their
                                ;entry point. Use ld -e foo to override the default.
_start:
                                ;write our string to stdout
    mov     edx,msg2.len2       ;third argument: message length
    mov     ecx,msg2            ;second argument: pointer to message to write
    mov     ebx,1               ;first argument: file handle (stdout)
    mov     eax,4               ;system call number (sys_write)
    int     0x80                ;call kernel

                                ;and exit
    mov     ebx,0               ;first syscall argument: exit code
    mov     eax, strict dword 1 ;system call number (sys_exit)
    int     0x80                ;call kernel
section .data                   ;section declaration
msg db      "Hello, world!",0xA ;our dear string
len equ     $ - msg             ;length of our dear string
msg2 db     "Hello, world2",0xA ;our dear string
.len2 equ     $ - msg2          ;length of our dear string
