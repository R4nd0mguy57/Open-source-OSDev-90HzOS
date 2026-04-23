#ifndef KB_TOOLS_H
    #define KB_TOOLS_H
    #define STRING_H
    #include "../string.h"

    unsigned char get_key(){
        extern volatile unsigned char Scan_code;
        unsigned char value = Scan_code;
        return value;
    }

    unsigned char shift_key(unsigned char target){
        if (target >= 97 && target <= 122){
            target -= 32;
        }
        else {
            switch (target){
                case '1':
                    target = '!';
                    break;
                case '2':
                    target = '@';
                    break;
                case '3':
                    target = '#';
                    break;
                case '4':
                    target = '$';
                    break;
                case '5':
                    target = '%';
                    break;
                case '6':
                    target = '^';
                    break;
                case '7':
                    target = '&';
                    break;
                case '8':
                    target = '*';
                    break;
                case '9':
                    target = '(';
                    break;
                case '0':
                    target = ')';
                    break;
                case '-':
                    target = '_';
                    break;
                case '=':
                    target = '+';
                    break;
                case '[':
                    target = '{';
                    break;
                case ']':
                    target = '}';
                    break;
                case ';':
                    target = ':';
                    break;
                case '\'':
                    target = '\"';
                    break;
                case '\\':
                    target = '|';
                    break;
                case ',':
                    target = '<';
                    break;
                case '.':
                    target = '>';
                    break;
                case '/':
                    target = '?';
                    break;
            }
        }
        return target;
    }

    char* get_att(char key){
        static char output[10];
        extern volatile unsigned char Ctrl_pressed;
        extern volatile unsigned char LeftShiftPressed;
        extern volatile unsigned char RightShiftPressed;
        extern volatile unsigned char ToogleCaps;
        extern volatile unsigned char Alt_pressed;
        extern volatile char Ctrl_combine[];
        extern volatile unsigned char combine_idx;
        if (Ctrl_pressed && key == 0x1D){
            output[0] = '\0';                   // Left Ctrl + None
            output[1] = '\0';
            output[7] = '\1';
            output[8] = '\0';
            output[9] = '\1';
            return output;
        }

        if (Alt_pressed && key == 0x38){
            if (!Ctrl_pressed){
                output[0] = 0;
            }
            output[6] = '\1';
            output[7] = Ctrl_pressed;
            output[8] = 0;
            output[9] = '\1';
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
            switch (Scan_code){
                case 0x1C:case 0x9C:
                    output[0] = '\r';
                    break;
                case 0x0E:case 0x8E:
                    output[0] = '\x08';
                    break;
                case 0x0F:case 0x8F:
                    output[0] = '\t';
                    break;
                default:
                    output[0] = 0;
                    break;
            }
        }
        if (ifchar){
            switch (Scan_code){
                case 0x02:case 0x82:
                    output[0] = '1';
                    break;
                case 0x03:case 0x83:
                    output[0] = '2';
                    break;
                case 0x04:case 0x84:
                    output[0] = '3';
                    break;
                case 0x05:case 0x85:
                    output[0] = '4';
                    break;
                case 0x06:case 0x86:
                    output[0] = '5';
                    break;
                case 0x07:case 0x87:
                    output[0] = '6';
                    break;
                case 0x08:case 0x88:
                    output[0] = '7';
                    break;
                case 0x09:case 0x89:
                    output[0] = '8';
                    break;
                case 0x0A:case 0x8A:
                    output[0] = '9';
                    break;
                case 0x0B:case 0x8B:
                    output[0] = '0';
                    break;
                case 0x0C:case 0x8C:
                    output[0] = '-';
                    break;
                case 0x0D:case 0x8D:
                    output[0] = '=';
                    break;
                case 0x10:case 0x90:
                    output[0] = 'q';
                    break;
                case 0x11:case 0x91:
                    output[0] = 'w';
                    break;
                case 0x12:case 0x92:
                    output[0] = 'e';
                    break;
                case 0x13:case 0x93:
                    output[0] = 'r';
                    break;
                case 0x14:case 0x94:
                    output[0] = 't';
                    break;
                case 0x15:case 0x95:
                    output[0] = 'y';
                    break;
                case 0x16:case 0x96:
                    output[0] = 'u';
                    break;
                case 0x17:case 0x97:
                    output[0] = 'i';
                    break;
                case 0x18:case 0x98:
                    output[0] = 'o';
                    break;
                case 0x19:case 0x99:
                    output[0] = 'p';
                    break;
                case 0x1A:case 0x9A:
                    output[0] = '[';
                    break;
                case 0x1B:case 0x9B:
                    output[0] = ']';
                    break;
                case 0x1E:case 0x9E:
                    output[0] = 'a';
                    break;
                case 0x1F:case 0x9F:
                    output[0] = 's';
                    break;
                case 0x20:case 0xA0:
                    output[0] = 'd';
                    break;
                case 0x21:case 0xA1:
                    output[0] = 'f';
                    break;
                case 0x22:case 0xA2:
                    output[0] = 'g';
                    break;
                case 0x23:case 0xA3:
                    output[0] = 'h';
                    break;
                case 0x24:case 0xA4:
                    output[0] = 'j';
                    break;
                case 0x25:case 0xA5:
                    output[0] = 'k';
                    break;
                case 0x26:case 0xA6:
                    output[0] = 'l';
                    break;
                case 0x27:case 0xA7:
                    output[0] = ';';
                    break;
                case 0x28:case 0xA8:
                    output[0] = '\'';
                    break;
                case 0x29:case 0xA9:
                    output[0] = '`';
                    break;
                case 0x2B:case 0xAB:
                    output[0] = '\\';
                    break;
                case 0x2C:case 0xAC:
                    output[0] = 'z';
                    break;
                case 0x2D:case 0xAD:
                    output[0] = 'x';
                    break;
                case 0x2E:case 0xAE:
                    output[0] = 'c';
                    break;
                case 0x2F:case 0xAF:
                    output[0] = 'v';
                    break;
                case 0x30:case 0xB0:
                    output[0] = 'b';
                    break;
                case 0x31:case 0xB1:
                    output[0] = 'n';
                    break;
                case 0x32:case 0xB2:
                    output[0] = 'm';
                    break;
                case 0x33:case 0xB3:
                    output[0] = ',';
                    break;
                case 0x34:case 0xB4:
                    output[0] = '.';
                    break;
                case 0x35:case 0xB5:
                    output[0] = '/';
                    break;
                case 0x39:case 0xB9:
                    output[0] = ' ';
                    break;
                default:
                    output[0] = 0;
                    break;
            }
        }
        if (ToogleCaps ^ (LeftShiftPressed || RightShiftPressed)){
            unsigned char shifted_key = shift_key(output[0]);
            output[0] = shifted_key;
        }        
        if(Ctrl_pressed && key != 0x1D){
            if (combine_idx >= 5){
                replace_string(output, Ctrl_combine);
                output[6] = Alt_pressed;
                output[7] = 1;
                output[8] = 0;
                output[9] = 1;
                return output;
            }
            if (!release){
                Ctrl_combine[combine_idx++] = output[0];
                Ctrl_combine[combine_idx] = '\0';
            }
            else {
                if (combine_idx > 0){
                    Ctrl_combine[combine_idx-1] = '\0';
                    combine_idx--;
                }
            }
            replace_string(output, Ctrl_combine);
            output[6] = Alt_pressed;
            output[7] = 1;
            output[8] = 0;
            output[9] = 0;
            return output;
        }
        else if (Alt_pressed && key != 0x38 && (!Ctrl_pressed)){
            output[6] = 1;
            output[7] = 1;
        }
        output[9] = release;
        output[8] = ifchar;
        return output;
    }

    
#endif