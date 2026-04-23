#ifndef PORTS_H
    #define PORTS_H
    #define PIC1            0x20
    #define PIC2            0xA0
    #define PIC1_COMMAND    PIC1
    #define PIC1_DATA       (PIC1+1)
    #define PIC2_COMMAND    PIC2
    #define PIC2_DATA       (PIC2+1)
    #define PIC_EOI         0x20        // End of Interrupt

    unsigned char inb(unsigned short port);
    void outb(unsigned short port, unsigned char value);
    
#endif