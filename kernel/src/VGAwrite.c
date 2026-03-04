#include "./headers/VGAwrite.h"
#include "./headers/utils.h"


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


size_t terminal_row = 0;
size_t terminal_col = 0;
uint16_t terminal_color = 0;
uint16_t* terminal_buffer = (uint16_t*)VGA_TEXT_ENTRY;


static uint16_t vga_char_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}


static uint16_t vga_entry(unsigned char c, uint16_t color){
	return (uint16_t) c | (uint16_t) color << 8;
}


void init_terminal(void){
	
	terminal_row = 0;
	terminal_col = 0;
	terminal_color = vga_char_color(VGA_GREEN, VGA_BLACK);
	
	for(size_t y = 0; y < 25; y++){
		for(size_t x = 0; x < 80; x++){
			const size_t index = y * 80 + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	
}


void set_terminal_color(uint16_t color){
	 terminal_color = color;
}


void terminal_putentry_at(char c, uint8_t color, size_t x, size_t y){
	const size_t index = y * 80 + x;
	terminal_buffer[index] = vga_entry(c, color);
}


void terminal_putchar(char c){
	terminal_putentry_at(c, terminal_color, terminal_col, terminal_row);
	if(terminal_col == 80){
		terminal_col = 0;
		if(terminal_row == 25){
			terminal_row = 0;
		}
	} 
}


void terminal_write(const char* data, size_t lenght){
	for(size_t i = 0; i < lenght; i++){
		terminal_putchar(data[i]);
	}
}


void terminal_writestring(const char* data){
	terminal_write(data, strlen(data));
}







