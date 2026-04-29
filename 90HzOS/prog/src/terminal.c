#include "include/terminal.h"
#include "../../kernel/src/include/string.h"
#include "../../kernel/src/include/kernel.h"
#include "../../kernel/src/include/drivers/keyboard/kb_tools.h"

void next_entry(int clear, unsigned int *position){
    init_keys();
    if (clear >= 1){
        clear_screen();
    }
    print_string("--------------------------------------------------------------------------------Executed Prog", 0x0F, position);

    prompt(position);
}

/*struct output {
        unsigned char char1;
        unsigned char char2;
        unsigned char char3;
        unsigned char char4;
        unsigned char char5;
        unsigned char char6;
        unsigned char Altpressed;
        unsigned char Ctrlpressed;
        unsigned char ifchar;
        unsigned char released;
    };*/

void prompt(unsigned int *position){
    print_string("\n[90HzOS]$ ", 0x0F, position);
    print_char(0, 0xF0, position);
    --*(position);
    struct output trans_key;
    unsigned char key=0;
    unsigned Oldkey = key;
    char full_command[4096];
    unsigned int command_pos = 0;
    unsigned int prompt_pos = *(position);
    while (1){
        Oldkey = key;
        key = get_key();
        if (key == Oldkey){
            continue;
        }
        trans_key = transkey(key);
        if (trans_key.char1 == '\r' || trans_key.char1 == '\t'){
            if (trans_key.char1 == '\r' && !trans_key.released){
                while (!trans_key.released){
                    key = get_key();
                    trans_key = transkey(key);
                }
                --*(position);
                print_char(0, 0x0F, position);
                prompt(position);
                return;
            }
            else {
                continue;
            }
        }
        if (trans_key.char1 == '\x08' && !trans_key.released){
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
        if (!trans_key.released && trans_key.char1 != 0){
            *(full_command + command_pos) = trans_key.char1;
            command_pos += 1;
            *(position) = prompt_pos;
            *(full_command + command_pos) = 0;
            print_string(full_command, 0x0F, position);
            print_char(0, 0xF0, position);
            continue;
        }
    }
}