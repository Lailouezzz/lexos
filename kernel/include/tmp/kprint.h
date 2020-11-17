#ifndef H_TMP_KPRINT
#define H_TMP_KPRINT
#include <stdint.h>
#include <stdarg.h>
#include "io/port.h"


#define VGA_CHAR_BY_LINE    80
#define VGA_TEXT_FB         0xB8000


int vga_text_putc(const char c);
void vga_text_set_color(const uint8_t forcolor, const uint8_t backcolor);
void vga_text_set_cursor(const uint8_t x, const uint8_t y);
void vga_text_return(void);

int kvprint(const char *fmt, va_list args);
int kprint(const char *fmt, ...);


#endif /// #ifndef H_TMP_KPRINT
