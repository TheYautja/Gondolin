#ifndef VGA_WRITE_H
#define VGA_WRITE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VGA_TEXT_ENTRY 0xB8000
#define TWIDTH 80
#define THEIGHT 25


extern size_t terminal_row;
extern size_t terminal_col;
extern uint16_t terminal_color;
extern uint16_t* terminal_buffer;


enum vga_color;

static uint16_t vga_char_color(enum vga_color fg, enum vga_color bg);
static uint16_t vga_entry(unsigned char c, uint16_t color);
void write_string( int colour, const char *string );
void init_terminal(void);
void set_terminal_color(uint16_t color);
void terminal_putentry_at(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t lenght);
void terminal_writestring(const char* data);

#endif
