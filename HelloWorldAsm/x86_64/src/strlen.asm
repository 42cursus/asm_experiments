BITS 64

global _start

section .text
_strlen:

  push  rcx            ; save and clear out counter
  xor   rcx, rcx

_strlen_next:

  cmp   [rsi], byte 0  ; null byte yet?
  jz    _strlen_null   ; yes, get out

  inc   rcx            ; char is ok, count it
  inc   rsi            ; move to next char
  jmp   _strlen_next   ; process again

_strlen_null:

  mov   rax, rcx       ; rcx = the length (put in rax)

  pop   rcx            ; restore rcx
  ret                  ; get out

_start:
  xor   rsi, rsi
  mov   rsi, msg      ; rsi is the string we want to
                      ; get the length of

  call  _strlen       ; get the length!

  mov   rdx, rax      ; rdx now holds the string length
                      ; ready for our write syscall

  ; write(fd, buf, len)
  mov   rax, 1        ; syscall 1 == write
  mov   rdi, 1        ; fd = 1 == stdout
  mov   rsi, msg      ; rsi is the string we want to
  syscall             ; print the string

  mov rax, 60       ; exit(
  mov rdi, 0        ;   EXIT_SUCCESS
  syscall           ; );

section .data
msg:    db  "Wello, horld!",10,0x0
section .rodata
msg2:   db  "Hello, world!",0xA,0x0;
