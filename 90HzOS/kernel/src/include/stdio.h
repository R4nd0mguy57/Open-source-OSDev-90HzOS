#ifndef STDIO_H
    #define STDIO_H
    #include "kernel.h"

        void clear_screen(){
            for (unsigned int i=0; i<(VGA_SCREEN_WIDTH*VGA_SCREEN_HEIGHT); ++i){
                *((unsigned char*)VRAM_CHAR_ADR+(i*2)) = 0;
                *((unsigned char*)VRAM_ATT_ADR+(i*2)) = 0x0F;
            }
        }

    void print_char(const char displayed_char, const char attributes, unsigned int *position){
        if (displayed_char != '\n' && displayed_char != '\t'){
            *((unsigned char*)VRAM_CHAR_ADR+(*position*2)) = displayed_char;
            *((unsigned char*)VRAM_ATT_ADR+(*position*2)) = attributes;
            ++(*position);
            return;
        }
        else if (displayed_char == '\n'){
            *(position) += 80 - (*position % 80);
            return;
        }
        else if(displayed_char == '\t'){
            unsigned int spaces= 4-(*position % 4);
            for (unsigned int i=0; i<spaces; ++i){
                *((unsigned char*)VRAM_CHAR_ADR+(*position*2)) = ' ';
                *((unsigned char*)VRAM_ATT_ADR+(*position*2)) = attributes;
                ++(*position);
            }
            return;
        }
    }

    void print_string(const char *string, const char attributes, unsigned int *position){
        for (int i=0; *(string+i)!='\0'; ++i){
            print_char(*(string+i), attributes, position);
        }
    }

    void set_BGcolor(const char color){
        for (unsigned int i=0; i<(VGA_SCREEN_WIDTH*VGA_SCREEN_HEIGHT); ++i){
            *((unsigned char*)VRAM_ATT_ADR+(i*2)) = color;
        }
    }
#endif