BITS 64

global _start

section .text
_start:
  mov rax, strict qword 1 ; write
  mov rdi, 1 ; stdout
  mov rsi, msg
  mov rdx, msg.len
  syscall
  
  mov rax, strict qword 60 ; exit  
  mov rdi, 0
  syscall

section .rodata
msg: db "Hello, World!", 10
.len: equ $ - msg
