#include "./headers/VGAwrite.h"
#include "./headers/utils.h"

#define TWIDTH 80;
#define THEIGHT 25;

enum vga_color {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_MAGENTA = 5,
	VGA_BROWN = 6,
	VGA_LIGHT_GREY = 7,
	VGA_DARK_GREY = 8,
	VGA_LIGHT_BLUE = 9,
	VGA_LIGHT_GREEN = 10,
	VGA_LIGHT_CYAN = 11,
	VGA_LIGHT_RED = 12,
	VGA_LIGHT_MAGENTA = 13,
	VGA_LIGHT_BROWN = 14,
	VGA_WHITE = 15,
};


uint16_t vga_char_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}


uint16_t vga_entry(unsigned char c, uint16_t color){
	return (uint16_t) c | (uint16_t) color << 8;
}


void init_terminal(void){
	
	terminal_row = 0;
	terminal_col = 0;
	terminal_color = vga_char_color(VGA_GREEN, VGA_DARK_GREY);
	
	for(size_t y = 0; y < THEIGHT; y++){
		for(size_t x = 0; x < TWIDTH; x++){
			const size_t index = y * TWIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	
}






