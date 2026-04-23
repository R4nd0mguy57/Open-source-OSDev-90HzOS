#include "include/kernel.h"
#include "include/keyboard/ps2.h"
#include "include/stdio.h"
#include "include/ports.h"
#include "../../prog/src/include/terminal.h"

void main(){
    unsigned int position = 0;
    char string[] = "Booted into main function of kernel.c at 0x100000!\n";
    clear_screen();
    print_string(string, 0x06, &position);
    init_idt();
    kb_init();
    enable_int();
    replace_string(string, "Initialized keyboard.\n");
    print_string(string, 0x0F, &position);
    replace_string(string, "Hello From 90HzOS!\n");
    print_string(string, 0x4F, &position);
    terminal_entry(0, &position);
    return ;
}

unsigned char handle_kb(){
    int extended_key = 0;
    unsigned char status = inb(KB_COMMAND);
    unsigned char keycode = 0;
    if (status & 1){
        keycode = inb(KB_DATA);       // If status, scan kb
    }
    /*if (keycode == 0xE0){
                                Coming soon ig
    }*/
    outb(PIC1_COMMAND, PIC_EOI);
    return keycode;
}

