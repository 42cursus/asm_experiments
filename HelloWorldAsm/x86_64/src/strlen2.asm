; https://stackoverflow.com/questions/42655541
; https://tuttlem.github.io/2013/01/08/strlen-implementation-in-nasm.html

global _strlen2

section .text

_strlen2:

  push  rbx                 ; save any registers that
  push  rcx                 ; we will trash in here

  mov   rbx, rdi            ; rbx = rdi

  xor   al, al              ; the byte that the scan will
                            ; compare to is zero
  cld                       ; left to right or auto-increment mode
  xor   ecx,ecx             ; rcx = 0
  dec   rcx                 ; rcx = -1 (0xFFFFFFFFFFFFFFFF)
                            ; the maximum number of bytes
                            ; i'm assuming any string will
                            ; have is 4gb

repne scasb                 ; while [rdi] != al, keep scanning

  sub   rdi, rbx            ; length = dist2 - dist1
  sub   rdi, 1              ; fix that into "string length" (-1 for '\0')
  mov   rax, rdi            ; rax now holds our length

  pop   rcx                 ; restore the saved registers
  pop   rbx

  ret                       ; all done!