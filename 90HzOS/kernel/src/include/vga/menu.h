#ifndef MENU_H
    #define MENU_H

    struct menu {
        char highlight_color;
        unsigned int default_string;
        char* strings[100];
    };

    void create_menu(struct menu menu_settings, unsigned int *position){
        extern volatile unsigned char Begin_menu_pos;
        extern volatile unsigned char End_menu_pos;
        unsigned int index;
        unsigned int str_nbr;
        if (menu_settings.default_string <= 100){
            index = menu_settings.default_string;
        }
        else {
            return;
        }
        Begin_menu_pos = *(position);
        unsigned int Begin_menu_pos_local = Begin_menu_pos;
        for (unsigned int i = 0; *(menu_settings.strings + i) != 0 && i <= 100; ++i){
            if (i+1 == index){
                print_string(*(menu_settings.strings + i), menu_settings.highlight_color, position);  // ** pointer == string array
            }
            else {
                print_string(*(menu_settings.strings + i), 0x0F, position);                           // ** pointer
            }
            print_char('\n', 0x00, position);
            str_nbr = i+1;
        }
        End_menu_pos = *(position);
        unsigned int Enter_pressed = 0;
        unsigned char key = 0;
        struct output trans_key;
        unsigned int choice;

        // Init
        trans_key.char1 = 0;
        trans_key.extended = 0;
        trans_key.Ctrlpressed = 0;
        trans_key.Altpressed = 0;

        while (!Enter_pressed){
            while (!trans_key.extended && trans_key.char1 != '\r'){
                key = get_key();
                trans_key = transkey(key);
            }
            switch (trans_key.char1){
                case 'U':
                    index -= 1;
                    break;
                case 'D':
                    index += 1;
                    break;
                case '\r':
                    Enter_pressed = 1;
                    break;
                default:
                    continue;
            }
            if (Enter_pressed){
                choice = index;
                return;
            }
            if (index < 1){
                index = str_nbr;
            }
            else if (index > str_nbr){
                index = 0;
            }

            // Render
            *(position) = Begin_menu_pos_local;
            for (unsigned int i = 0; *(menu_settings.strings + i) != 0 && i <= 100; ++i){
                if (i+1 == index){
                    print_string(*(menu_settings.strings + i), menu_settings.highlight_color, position);  // ** pointer == string array
                }
                else {
                    print_string(*(menu_settings.strings + i), 0x0F, position);                           // ** pointer
                }
                print_char('\n', 0x00, position);
            }
        }

    }
#endif