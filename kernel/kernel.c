#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "headers/utils.h"
#include "headers/VGAwrite.h"


#if defined(__linux__)
#error "cross compiler not found"
#endif


#if !defined(__i386__)
#error "needs a x86 compiler"
#endif


void kernel_main(void){
	
	const char* out = "bing chilling";
	write_string(5, out);
	
}
