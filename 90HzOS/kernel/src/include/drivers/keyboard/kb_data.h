#ifndef KB_DATA_H
    #define KB_DATA_H

    void init_arrays(void);

    struct output {
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
        unsigned char extended;
    };

    const char scan_codes_arr[256] = {
        0,
        '\x1b',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        '0',
        '-',
        '=',
        '\x08',
        '\t',
        'q',
        'w',
        'e',
        'r',
        't',
        'y',
        'u',
        'i',
        'o',
        'p',
        '[',
        ']',
        '\r',
        0,
        'a',
        's',
        'd',
        'f',
        'g',
        'h',
        'j',
        'k',
        'l',
        ';',
        '\'',
        '`',
        0,
        '\\',
        'z',
        'x',
        'c',
        'v',
        'b',
        'n',
        'm',
        ',',
        '.',
        '/',
        0,
        '*',
        0,
        ' ',
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        '7',
        '8',
        '9',
        '-',
        '4',
        '5',
        '6',
        '+',
        '1',
        '2',
        '3',
        '0',
        '.',
        0,
        0,
        '\x1b',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        '0',
        '-',
        '=',
        '\x08',
        '\t',
        'q',
        'w',
        'e',
        'r',
        't',
        'y',
        'u',
        'i',
        'o',
        'p',
        '[',
        ']',
        '\r',
        0,
        'a',
        's',
        'd',
        'f',
        'g',
        'h',
        'j',
        'k',
        'l',
        ';',
        '\'',
        '`',
        0,
        '\\',
        'z',
        'x',
        'c',
        'v',
        'b',
        'n',
        'm',
        ',',
        '.',
        '/',
        0,
        '*',
        0,
        ' ',
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        '7',
        '8',
        '9',
        '-',
        '4',
        '5',
        '6',
        '+',
        '1',
        '2',
        '3',
        '0',
        '.',
        0,
        0,
    };

    char extended_keys_arr[256];
    char shifted_keys_arr[256];
    char letters[27] = "qwertyuiopasdfghjklzxcvbnm";

    void init_arrays(void){
        // extended

        *(extended_keys_arr + 0x35) = '/';
        *(extended_keys_arr + 0xB5) = '/';
        *(extended_keys_arr + 0x48) = 'U';
        *(extended_keys_arr + 0xC8) = 'U';
        *(extended_keys_arr + 0x4B) = 'L';
        *(extended_keys_arr + 0xCB) = 'L';
        *(extended_keys_arr + 0x4D) = 'R';
        *(extended_keys_arr + 0xCD) = 'R';
        *(extended_keys_arr + 0x50) = 'D';
        *(extended_keys_arr + 0xD0) = 'D';
        *(extended_keys_arr + 0x1C) = '\r';
        *(extended_keys_arr + 0x9C) = '\r';

        // Shifted

        *(shifted_keys_arr + '1') = '!';
        *(shifted_keys_arr + '2') = '@';
        *(shifted_keys_arr + '3') = '#';
        *(shifted_keys_arr + '4') = '$';
        *(shifted_keys_arr + '5') = '%';
        *(shifted_keys_arr + '6') = '^';
        *(shifted_keys_arr + '7') = '&';
        *(shifted_keys_arr + '8') = '*';
        *(shifted_keys_arr + '9') = '(';
        *(shifted_keys_arr + '0') = ')';
        *(shifted_keys_arr + '-') = '_';
        *(shifted_keys_arr + '=') = '+';
        *(shifted_keys_arr + '[') = '{';
        *(shifted_keys_arr + ']') = '}';
        *(shifted_keys_arr + ';') = ':';
        *(shifted_keys_arr + '\'') = '\"';
        *(shifted_keys_arr + '\\') = '|';
        *(shifted_keys_arr + ',') = '<';
        *(shifted_keys_arr + '.') = '>';
        *(shifted_keys_arr + '/') = '?';
    } 

#endif