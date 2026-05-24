#ifndef TERMINAL_H
    #define TERMINAL_H

    void next_entry(int clear);
    void prompt(volatile unsigned int *position);
    unsigned int parse(volatile unsigned int* position, const char* full_command);

#endif