#ifndef MEM_ALLOCH

    #define MEM_ALLOCH

    unsigned int* malloc(unsigned int size);
    void free(unsigned int* ALLOC_ADR);
    unsigned int get_remain_heap_RAM();

    unsigned int* malloc(unsigned int size){
        // Invalid Size
        if (size == 0){
            return 0x0;
        }
        // Makes size % 4
        size += 4 - (size % 4);
        size /= 4;
        unsigned int ALLOC_IDX = 0;
        unsigned int size_offset = 0;
        unsigned int* ret = 0;
        unsigned char status;
        unsigned int free_size;
        do {
            if (*(HEAP_START + ALLOC_IDX + size_offset) != 1 && *(HEAP_START + ALLOC_IDX + size_offset + 1) >= size * 4){
                status = *(HEAP_START + ALLOC_IDX + size_offset);
                free_size = *(HEAP_START + ALLOC_IDX + size_offset + 1);
                *(HEAP_START + ALLOC_IDX + size_offset + 1) = 1;
                *(HEAP_START + ALLOC_IDX + size_offset + 2) = size * 4;
                ret = (HEAP_START + ALLOC_IDX + size_offset + 3);
                size_offset += size;

                if (status == 0){
                    *(HEAP_START + ALLOC_IDX + size_offset + 1) = 0;
                    if (*(&status + (free_size / 4)+1) == 0){
                        *(HEAP_START + ALLOC_IDX + size_offset + 2) = *(&status + (free_size / 4)+1) + size*4;
                    }
                }
                else {
                    *(HEAP_START + ALLOC_IDX + size_offset + 3) = 2;
                    unsigned int remain_RAM = get_remain_heap_RAM();
                    *(HEAP_START + ALLOC_IDX + size_offset + 4) = remain_RAM;
                }
                break;
        
            }
            size_offset += *(HEAP_START + ALLOC_IDX + size_offset + 1)/4;
            ++ALLOC_IDX;

        } while (ret == 0);
        return ret;
    }

    /*void free(unsigned int* ALLOC_ADR){
        enum boolean last = *(ALLOC_ADR + ((*(ALLOC_ADR - 1))/4)) == 2;
        if (last){
            *(ALLOC_ADR - 2) = 2;
        }
        else {
            *(ALLOC_ADR - 2) = 0;
        }
    }*/

    void write_string(unsigned char* string, unsigned int* STR_TARGET){
        for (unsigned int i = 0; *string != 0; ++i){
            *((unsigned char*)STR_TARGET + i) = *string;
            ++string;
        }
        return;
    }

    unsigned int get_remain_heap_RAM(){
        unsigned char status = *(HEAP_START);
        unsigned int size_offset = 0;
        unsigned int ALLOC_IDX = 0;
        for (unsigned int i = 0; status != 2; ++i){
            status = *(HEAP_START + ALLOC_IDX + size_offset);
            size_offset += *(HEAP_START + ALLOC_IDX + size_offset + 1)/4;
            ALLOC_IDX += 1;
        }
        unsigned int remain_RAM = initRAMstruct.total_RAM;
        remain_RAM -= (remain_RAM % 4);
        remain_RAM -= size_offset * 4 - ALLOC_IDX+1 - (unsigned int)HEAP_START;
        remain_RAM -= (remain_RAM % 4);
        return remain_RAM;
    }


#endif