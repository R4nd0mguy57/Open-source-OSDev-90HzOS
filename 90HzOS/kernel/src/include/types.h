#ifndef TYPES_H
    #define TYPES_H

    enum _null {
        _NULL = -1,
    };

    enum boolean {
        True  = 1,
        False = 0,
    };

    typedef unsigned    int     u32;
    typedef signed      int     i32;
    typedef unsigned    short   u16;
    typedef signed      short   i16;
    typedef unsigned    char    u8;
    typedef signed      char    i8;

    typedef enum boolean        _bool;
    typedef enum _null          _NULL;

#endif