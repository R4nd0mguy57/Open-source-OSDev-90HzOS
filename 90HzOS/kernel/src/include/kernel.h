#ifndef KERNEL_H
    #define KERNEL_H

    #define KB_COMMAND 0x64
    #define KB_DATA 0x60

    #define VRAM_CHAR_ADR 0xB8000
    #define VRAM_ATT_ADR 0xB8001
    #define VGA_SCREEN_WIDTH 80
    #define VGA_SCREEN_HEIGHT 25
    
void clear_screen(volatile unsigned int* position);
void print_char(volatile const char displayed_char, const char attributes, volatile unsigned int *position);
void print_string(volatile const char *string, const char attributes,volatile  unsigned int *position);
void set_BGcolor(const char color);
void replace_string(volatile char *string, volatile char *target);

unsigned char handle_kb();

#endif