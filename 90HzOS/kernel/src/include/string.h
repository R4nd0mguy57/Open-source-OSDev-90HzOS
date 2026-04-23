#ifndef STRING_H
    #define STRING_H

    void replace_string(char *string, volatile char *target){
        unsigned int index=0;
        do {
            *(string+index) = *(target+index);
            ++index;
        }   while (*(target+index) != '\0');
        *(string+index) = '\0';
    }

    int length(volatile char* string){
        int length = 0;
        for (unsigned int i=0; *(string+i)!='\0'; ++i){
            length += 1;
        }
        return length;
    }

    int compare_string(char* string1, char* string2){
        unsigned int len1 = length(string1);
        unsigned int len2 = length(string2);
        if (len1 != len2){
            return 0;
        }
        else {
            for (unsigned int i=0; i<len1; ++i){
                if (string1[i] != string2[i]){
                    return 0;
                }
                continue;
            }
        }
        return 1;

    }

#endif