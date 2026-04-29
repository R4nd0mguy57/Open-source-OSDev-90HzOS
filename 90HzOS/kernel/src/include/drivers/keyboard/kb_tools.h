#ifndef KB_TOOLS_H
    #define KB_TOOLS_H
    #define STRING_H
    #include "../../string.h"
    #include "kb_data.h"
    
    struct output extended_char(unsigned char scan_code);

    unsigned char get_key(){
        extern volatile unsigned char Scan_code;
        unsigned char value = Scan_code;
        return value;
    }

    unsigned char shift_key(unsigned char target){
        if (target >= 97 && target <= 122){
            target -= 32;
        }
        else if (target != '\r' && target != '\x08'){
            target = shifted_keys_arr[target];
        }
        return target;
    }

    void init_keys(void){
        init_arrays();
    }

    struct output transkey(char key){
        struct output output;
        extern volatile unsigned char extended;
        extern volatile unsigned char Ctrl_pressed;
        extern volatile unsigned char LeftShiftPressed;
        extern volatile unsigned char RightShiftPressed;
        extern volatile unsigned char ToogleCaps;
        extern volatile unsigned char Alt_pressed;
        extern volatile char Ctrl_combine[];
        extern volatile unsigned char combine_idx;
        if (!extended){
            if (Ctrl_pressed && key == 0x1D){
                output.char1 = 0;                   // Left Ctrl + None
                output.char2 = 0;
                output.Ctrlpressed = 1;
                output.ifchar = 0;
                output.released = 1;
                return output;
            }

            if (Alt_pressed && key == 0x38){
                if (!Ctrl_pressed){
                    output.char1 = 0;
                }
                output.Altpressed = 1;
                output.Ctrlpressed = Ctrl_pressed;
                output.ifchar = 0;
                output.released = 0;
                return output;
            }
            unsigned char Scan_code = key;
            int ifchar = 0;
            int release = 0;
            if (((Scan_code >= 2 && Scan_code < 14) || (Scan_code >= 16 && Scan_code < 28) || (Scan_code >= 30 && Scan_code < 42) || (Scan_code >= 43 && Scan_code < 54) || (Scan_code == 55) || (Scan_code == 0x39) || (Scan_code >= 71 && Scan_code < 87)) && Scan_code < 89){
                ifchar = 1;
                release = 0;
            }
            else if(((Scan_code >= 2+89 && Scan_code < 14+0x80) || (Scan_code >= 16+0x80 && Scan_code < 28+0x80) || (Scan_code >= 30+0x80 && Scan_code < 42+0x80) || (Scan_code >= 43+0x80 && Scan_code < 54+0x80) || (Scan_code == 55+0x80) || (Scan_code == 0xb9) || (Scan_code >= 71+0x80 && Scan_code < 87+0x80)) && Scan_code < 89+0x80) {
                ifchar = 1;
                release = 1;
            }
            else{
                ifchar = 0;
                if (Scan_code >= 0x81){
                    release = 1;
                }
                else {
                    release = 0;
                }
                output.char1 = scan_codes_arr[Scan_code];
            }
            if (ifchar){
                output.char1 = scan_codes_arr[Scan_code];
            }
            if (ToogleCaps ^ (LeftShiftPressed || RightShiftPressed)){
                unsigned char shifted_key = shift_key(output.char1);
                output.char1 = shifted_key;
            }        
            if(Ctrl_pressed && key != 0x1D){
                if (combine_idx >= 5){
                    output.char1 = Ctrl_combine[0];
                    output.char2 = Ctrl_combine[1];
                    output.char3 = Ctrl_combine[2];
                    output.char4 = Ctrl_combine[3];
                    output.char5 = Ctrl_combine[4];
                    output.char6 = Ctrl_combine[5];
                    output.Altpressed = Alt_pressed;
                    output.Ctrlpressed = 1;
                    output.ifchar = 0;
                    output.released = 1;
                    return output;
                }
                if (!release){
                    Ctrl_combine[combine_idx++] = output.char1;
                    Ctrl_combine[combine_idx] = 0;
                }
                else {
                    if (combine_idx > 0){
                        Ctrl_combine[combine_idx-1] = 0;
                        combine_idx--;
                    }
                }
                output.char1 = Ctrl_combine[0];
                output.char2 = Ctrl_combine[1];
                output.char3 = Ctrl_combine[2];
                output.char4 = Ctrl_combine[3];
                output.char5 = Ctrl_combine[4];
                output.char6 = Ctrl_combine[5];
                output.Altpressed = Alt_pressed;
                output.Ctrlpressed = 1;
                output.ifchar = 0;
                output.released = 0;
                return output;
            }
            else if (Alt_pressed && key != 0x38 && (!Ctrl_pressed)){
                output.Altpressed = 1;
                output.Ctrlpressed = 0;
            }
            output.released = release;
            output.ifchar = ifchar;
            output.extended = 0;
        }
        else {
            output = extended_char(key);
            extended = 0;
        }
        return output;
    }

    struct output extended_char(unsigned char scan_code){
        unsigned char released = (scan_code < 0x90);
        struct output output;
        output.extended = 1;
        output.released = released;
        output.char1 = extended_keys_arr[scan_code];
        if (output.char1 != '/'){
            output.ifchar = 0;
        }
        else {
            output.ifchar = 1;
        }
        output.Ctrlpressed = 0;
        output.Altpressed = 0;
        return output;
    }

    
#endif