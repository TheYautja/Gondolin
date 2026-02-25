#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#if defined(__linux__)
#error "cross compiler not found"
#endif


#if !defined(__i386__)
#error "needs a x86 compiler"
#endif


size_t strlen(const char* str){
	size_t len = 0;
	while(str[len]){
		len++;
	}
	return len;
}


void write_string( int colour, const char *string )
{
    volatile char *vmem = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}


void kernel_main(void){
	
	const char* out = "bing chilling";
	write_string(3, out);
	
}
