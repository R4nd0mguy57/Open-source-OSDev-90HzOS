#ifndef STDIO_H
    #define STDIO_H
    #include "../kernel.h"
    #define MOVE_GRID_BEGIN_CHAR 0xB80A0
    #define MOVE_GRID_BEGIN_ATT 0xB80A1
    #define MOVE_GRID_END 0xB8000 + (80*24)*2

    void change_color(const char color, unsigned int *position){
        *((unsigned char*)VRAM_ATT_ADR+(*position*2)) = color;
    }
    
    void clear_screen(){
        for (unsigned int i=0; i<(VGA_SCREEN_WIDTH*VGA_SCREEN_HEIGHT); ++i){
            *((unsigned char*)VRAM_CHAR_ADR+(i*2)) = 0;
            *((unsigned char*)VRAM_ATT_ADR+(i*2)) = 0x0F;
        }
    }
    


    void move_grid(unsigned int count){
        for (unsigned int i=0; i!=count; ++i){
            for (unsigned int j=0; j!=80*(25-1); ++j){
                *((unsigned char*)VRAM_CHAR_ADR+(j*2)) = *((unsigned char*)MOVE_GRID_BEGIN_CHAR+(j*2));
                *((unsigned char*)VRAM_ATT_ADR+(j*2)) = *((unsigned char*)MOVE_GRID_BEGIN_ATT+(j*2));
            }
        }
        for (unsigned int i=0; i!=25; ++i){
            *((unsigned char*)MOVE_GRID_END+(i*2)) = 0;
            *((unsigned char*)MOVE_GRID_END+1+(i*2)) = 0;
        }
    }

    void print_char(const char displayed_char, const char attributes, unsigned int *position){
        if (*position == 80*25){
            move_grid(1);
            *(position) -= 80;
        }
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