
default rel ; defaults to RIP-relative addressing for eligible memory operands

global main
extern printf

section .data
    ; dd = define doubleword (4 bytes per element)
    ; word = 16 bits, inherited from the original 8086 architecture
    arr dd 10, 20, 30, 40

    ; db = define byte
    ; "%d" = decimal integer format
    ; 10 = newline, 0 = null terminator
    fmt db "%d", 10, 0

section .text
main:
    lea r10, [arr]                ; R10 = address of arr[0]
                                  ; Address calculated relative to RIP

    mov esi, dword [r10 + 4]      ; ESI = arr[1] = 20
                                  ; Effective address = R10 + 4
                                  ; Read 4 bytes from memory

    lea rdi, [fmt]                ; RDI = address of format string

    xor eax, eax                  

    call printf wrt ..plt         ; wrt .. plt will use Procedure Linkage Table
                                  ; this is needed because printf is not part of our code - must be linked 
                                  ; System V ABI:
                                  ; RDI = 1st argument (format address)
                                  ; ESI = 2nd argument (integer 20)
                                  ; Equivalent to printf("%d\n", 20)

    xor eax, eax                  ; main returns 0 in EAX
                                  ; note that caller checkes EAX due to int return type
                                  ; Pointer -> RAX
                                
    ret                           ; Return to caller

