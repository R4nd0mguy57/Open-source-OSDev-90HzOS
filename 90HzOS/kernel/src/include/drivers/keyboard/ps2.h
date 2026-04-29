#ifndef PS2_H
    #define PS2_H

    struct IDT_entry {
        unsigned short offset_lower;
        unsigned short segment;
        unsigned char zero;
        unsigned char type;
        unsigned short offset_upper;
    }__attribute__((packed));

    struct IDT_pointer{
        unsigned short limit;
        unsigned int offset;
    }__attribute__((packed));

    extern void init_idt();
    extern void load_idt(struct IDT_pointer *idt);
    extern void enable_int();
    extern void kb_handler();

    void init_idt();
    void kb_init();
    unsigned char handle_kb();

#endif