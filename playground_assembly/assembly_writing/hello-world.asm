default rel 

global main

section .data
hellostring: db "Hello World!", 10
len: equ $ - hellostring

section .text
main:
    call print
    ret
    
print:
    mov rax, 1                 ;#sys-call write code
    mov rdi, 1                 ;#sys-call argument TERMINAL redirect to stdout
    lea rsi, [hellostring]     ;#address of string
    mov rdx, len               ;#number of bytes to read at address
    syscall
                                
    ret                           

