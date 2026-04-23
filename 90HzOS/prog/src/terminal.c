#include "include/terminal.h"
#include "../../kernel/src/include/string.h"
#include "../../kernel/src/include/kernel.h"
#include "../../kernel/src/include/keyboard/kb_tools.h"

void terminal_entry(int clear, unsigned int *position){
    if (clear >= 1){
        clear_screen();
    }
    print_string("--------------------------------------------------------------------------------Executed terminal\n", 0x0F, position);
    prompt(position);
    while(1){

    }
}

void prompt(unsigned int *position){
    print_string("\n[90HzOS]$ ", 0x0F, position);
    unsigned char Oldkey = 0;
    unsigned char key = 0;
    char* key_att;
    char full_command[256] = "";
    unsigned int command_pos = 0;
    const unsigned int prompt_pos = *position;
    extern volatile unsigned char Ctrl_pressed;
    while (1){
        Oldkey = key;
        key = get_key();
        if (Oldkey == key){
            continue;
        }
        key_att = get_att(key);
        if (key_att[0] == '\0' && (!Ctrl_pressed)){
            continue;
        }
        if (key_att[7] && key_att[0] == 'c' && key_att[1] == 'd'){
            print_string("BONDOUR!!", 0x04, position);
            continue;
        }
        if (!key_att[9] && key_att[0] == '\x08' && command_pos >= 1){
            command_pos -= 1;
            unsigned int len = length(full_command);
            full_command[len-1] = '\0';
            --*position;
            print_char(0, 0x00, position);
            *(position) = prompt_pos;
            print_string(full_command, 0x0F, position);
            print_char(0, 0xF0, position);
            continue;
        }
        if (!key_att[9] && key_att[8]){
            *(full_command + command_pos) = key_att[0];
            command_pos += 1;
            *position = prompt_pos;
            *(full_command + command_pos) = '\0';
            print_string(full_command, 0x0F, position);
            print_char(0, 0xF0, position);
            continue;
        }
    }

}