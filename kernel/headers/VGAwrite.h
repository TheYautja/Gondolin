#ifndef VGA_WRITE_H
#define VGA_WRITE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VGA_TEXT_ENTRY 0xB8000;

enum vga_color;

size_t terminal_row;
size_t terminal_col;
uint16_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_TEXT_ENTRY;

uint16_t vga_char_color(enum vga_color fg, enum vga_color bg);
uint16_t vga_entry(unsigned char c, uint16_t color);
void write_string( int colour, const char *string );
void init_terminal(void);

#endif
