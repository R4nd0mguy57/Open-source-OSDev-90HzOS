[BITS 32]

global _start
extern main
extern clear_screen

_start:
    call main
    mov ecx, 0
    call clear_screen
    mov esi, end_string
    call print_string
    hlt

print_string:
    cmp byte [esi], 0
    je return
    jne print_char
print_char:
    mov al, [esi]
    mov [0xB8000+ecx], al
    mov [0xB8001+ecx], 0x04
    add ecx, 2
    add esi, 1
    jmp print_string
return:
    mov esi, 0
    mov ecx, 0
    mov eax, 0
    ret

end_string: db "The Kernel stopped running.Your CPU has been stopped. It's now safe to turn off your computer!", 0