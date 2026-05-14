#ifndef STDIO_H
    #define STDIO_H
    #include "../kernel.h"
    #define MOVE_GRID_BEGIN_CHAR 0xB80A0
    #define MOVE_GRID_BEGIN_ATT 0xB80A1
    #define MOVE_GRID_END 0xB8000 + (80*24)*2

    void print_integer(int integer, volatile unsigned int* position);
    void print_uinteger(unsigned int uinteger, volatile unsigned int* position);

    void change_color(const char color, volatile unsigned int *position){
        *((unsigned char*)VRAM_ATT_ADR+(*position*2)) = color;
    }
    
    void clear_screen(volatile unsigned int* position){
        for (unsigned int i=0; i<(VGA_SCREEN_WIDTH*VGA_SCREEN_HEIGHT); ++i){
            *((unsigned char*)VRAM_CHAR_ADR+(i*2)) = 0;
            *((unsigned char*)VRAM_ATT_ADR+(i*2)) = 0x0F;
        }
        *position = 0;
    }

    void move_grid(unsigned int count){
        for (unsigned int i=0; i!=count; ++i){
            for (unsigned int j=0; j!=80*25; ++j){
                *((unsigned char*)VRAM_CHAR_ADR+(j*2)) = *((unsigned char*)MOVE_GRID_BEGIN_CHAR+(j*2));
                *((unsigned char*)VRAM_ATT_ADR+(j*2)) = *((unsigned char*)MOVE_GRID_BEGIN_ATT+(j*2));
            }
        }
        for (unsigned int i=0; i!=25; ++i){
            *((unsigned char*)MOVE_GRID_END+(i*2)) = 0;
            *((unsigned char*)MOVE_GRID_END+1+(i*2)) = 0;
        }
    }

    void print_char(volatile const char displayed_char, const char attributes, volatile unsigned int *position){
        extern volatile unsigned int Times_Grid_moved;
        if (*position-(Times_Grid_moved*80) >= (80*25-1)){
            move_grid(1);
            Times_Grid_moved += 1;
        }
        if (displayed_char != '\n' && displayed_char != '\t'){
            *((unsigned char*)VRAM_CHAR_ADR+((*position-(Times_Grid_moved*80))*2)) = displayed_char;
            *((unsigned char*)VRAM_ATT_ADR+((*position-(Times_Grid_moved*80))*2)) = attributes;
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

    void print_string(volatile const char *string, const char attributes, volatile unsigned int *position){
        for (int i=0; *(string+i)!='\0'; ++i){
            print_char(*(string+i), attributes, position);
        }
    }

    void set_BGcolor(const char color){
        for (unsigned int i=0; i<(VGA_SCREEN_WIDTH*VGA_SCREEN_HEIGHT); ++i){
            *((unsigned char*)VRAM_ATT_ADR+(i*2)) = color;
        }
    }

    void printf(const char* string, ...){
        extern volatile unsigned int position;
        extern volatile unsigned char Color;
        int* var_arg_ptr = (int*)(&string);                       // 4 bytes per inc
        for (int i = 0; *(string + i) != 0; ++i){
            if (*(string + i) != '%' && *(string + i) != '\033'){
                print_char(*(string + i), Color, &position);
            }
            else if(*(string + i) == '\033'){
                ++i;
                Color = *(string + i);
                continue;
            }
            else {
                ++var_arg_ptr;
                ++i;
                switch (*(string + i)){
                    case 'd':case 'i':
                        print_integer(*var_arg_ptr, &position);
                        break;
                    case 'u':
                        print_uinteger(*var_arg_ptr, &position);
                        break;
                    case 'c':
                        print_char(*var_arg_ptr, Color, &position);
                        break;
                    default:
                        return;
                }
                continue;
            }
        }
    }

    void print_integer(int integer, volatile unsigned int* position){
        extern volatile unsigned char Color;
        char int_string[11];
        unsigned int integer_str_len = 1;
        int integer_copy = integer;
        unsigned char int_to_char = 0;
        int extreme_values = 10;
        unsigned int sub_integer = 0;
        unsigned int extreme_values_cp = 10;
        int integers_string[11];

        while (integer_copy >= extreme_values || integer_copy <= (extreme_values * -1)){
            integer_copy /= 10;
            integer_str_len += 1;
        }

        if (integer < 0){
            print_char('-', Color, position);
        }

        for (unsigned int i = 0; i != integer_str_len; ++i){
            integer_copy = integer;
            if (integer_copy < 0){
                integer_copy *= -1;
            }

            while (integer_copy >= extreme_values && integer_copy >= (extreme_values * -1)){
                integer_copy /= 10;
            }

            if (i != 0){
                extreme_values_cp = extreme_values;
                sub_integer = 0;
                for (unsigned j = 0; j != i; ++j){
                    extreme_values_cp /= 10;
                    sub_integer += (extreme_values_cp) * (*(integers_string + j));
                }
                integer_copy -= sub_integer;
            }
            *(integers_string + i) = integer_copy;

            switch (integer_copy){
                case 0:
                    int_to_char = 48;
                    break;
                case 1:
                    int_to_char = 49;
                    break;
                case 2:
                    int_to_char = 50;
                    break;
                case 3:
                    int_to_char = 51;
                    break;
                case 4:
                    int_to_char = 52;
                    break;
                case 5:
                    int_to_char = 53;
                    break;
                case 6:
                    int_to_char = 54;
                    break;
                case 7:
                    int_to_char = 55;
                    break;
                case 8:
                    int_to_char = 56;
                    break;
                case 9:
                    int_to_char = 57;
                    break;
                default:
                    int_to_char = 0;
                    break;
            }
            extreme_values *= 10;
            *(int_string + i) = int_to_char;
        }
        *(int_string + integer_str_len) = 0;
        print_string(int_string, Color, position);
    }

    void print_uinteger(unsigned int uinteger, volatile unsigned int* position){
        extern volatile unsigned char Color;
        char uint_string[11];
        unsigned int uinteger_str_len = 1;
        unsigned int uinteger_copy = uinteger;
        unsigned char uint_to_char = 0;
        unsigned int extreme_values = 10;
        unsigned int sub_uinteger = 0;
        unsigned int extreme_values_cp = 10;
        unsigned int integers_string[11];

        while (uinteger_copy >= extreme_values){
            uinteger_copy /= 10;
            uinteger_str_len += 1;
        }

        for (unsigned int i = 0; i != uinteger_str_len; ++i){
            uinteger_copy = uinteger;

            while (uinteger_copy >= extreme_values){
                uinteger_copy /= 10;
            }

            if (i != 0){
                extreme_values_cp = extreme_values;
                sub_uinteger = 0;
                for (unsigned j = 0; j != i; ++j){
                    extreme_values_cp /= 10;
                    sub_uinteger += (extreme_values_cp) * (*(integers_string + j));
                }
                uinteger_copy -= sub_uinteger;
            }
            *(integers_string + i) = uinteger_copy;

            switch (uinteger_copy){
                case 0:
                    uint_to_char = 48;
                    break;
                case 1:
                    uint_to_char = 49;
                    break;
                case 2:
                    uint_to_char = 50;
                    break;
                case 3:
                    uint_to_char = 51;
                    break;
                case 4:
                    uint_to_char = 52;
                    break;
                case 5:
                    uint_to_char = 53;
                    break;
                case 6:
                    uint_to_char = 54;
                    break;
                case 7:
                    uint_to_char = 55;
                    break;
                case 8:
                    uint_to_char = 56;
                    break;
                case 9:
                    uint_to_char = 57;
                    break;
                default:
                    uint_to_char = 0;
                    break;
            }
            extreme_values *= 10;
            *(uint_string + i) = uint_to_char;
        }
        *(uint_string + uinteger_str_len) = 0;
        print_string(uint_string, Color, position);
    }

#endif