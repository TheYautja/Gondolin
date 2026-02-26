#include "./headers/VGAwrite.h"


void write_string( int colour, const char *string ){
    volatile char *vmem = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *vmem++ = *string++;
        *vmem++ = colour;
    }
}
