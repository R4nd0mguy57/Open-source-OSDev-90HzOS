#include "include/kernel.h"
#include "include/drivers/keyboard/ps2.h"
#include "include/vga/stdio.h"
#include "include/drivers/ports/ports.h"
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

    print_string("Source code: https://github.com/R4nd0mguy57/Open-source-OSDev-90HzOS/tree/main\n", 0x1F, &position);

    next_entry(0, &position);
    return;
}

int extended_key;

unsigned char handle_kb(){
    extern volatile unsigned char extended;
    unsigned char keycode = 0;
    if (!extended_key){
        unsigned char status = inb(KB_COMMAND);
        if (status & 1){
            keycode = inb(KB_DATA);       // If status, scan kb
        }
        if (keycode == 0xE0){
            extended_key = 1;
            keycode = handle_kb();
        }
        outb(PIC1_COMMAND, PIC_EOI);
        return keycode;
    }
    else {
        keycode = inb(KB_DATA);
        extended = 1;
        extended_key = 0;
        return keycode;
    }
}
