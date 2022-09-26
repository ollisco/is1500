// c main

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

int getsw(void)
{
    return (PORTD >> 8) & 0b1111; // return 11-8 bits
}

int getbtns(void)
{
    return (PORTD >> 5) & 0b111; // return 7-5 bits
}
