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
	*((int*)0xb8000)=0x07690748;
}
