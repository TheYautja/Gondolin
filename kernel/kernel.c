#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#if defined(__linux__)
#error "cross compiler not found"
#endif


#if !defined(__i386__)
#error "needs a x86 compiler"
#endif


void kernel_main(void){
	
	volatile unsigned char* vmem = (volatile unsigned char*)0xB8000;
	vmem[0] = 'Y';
	vmem[1] = 0xf0;
	vmem[2] = 'o';
	vmem[3] = 0xf0;
	
}
