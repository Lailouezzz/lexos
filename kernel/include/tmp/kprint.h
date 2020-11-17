#ifndef H_TMP_KPRINT
#define H_TMP_KPRINT
#include <stdint.h>
#include "io/port.h"


#define VGA_CHAR_BY_LINE    80
#define VGA_TEXT_FB         0xB8000


int vga_putc(const char c);
void vga_set_color(const uint8_t forcolor, const uint8_t backcolor);
void vga_set_cursor(const uint8_t x, const uint8_t y);

int kprint(const char *str);


#endif /// #ifndef H_TMP_KPRINT
