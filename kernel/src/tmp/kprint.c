#include "tmp/kprint.h"


/* Local variable */

static uint8_t current_curx = 0;
static uint8_t current_cury = 0;
static uint8_t current_color = 0x0F; /* forgroud : white | background : black */


int vga_putc(const char c)
{
    uint16_t formated_char = c | (current_color << 8);
    ((uint16_t*)VGA_TEXT_FB)[current_curx + (current_cury * 80)] = 
            formated_char;
    
    if (current_curx >= 79)
    {
        current_curx = 0;
        current_cury++;
    }
    else
    {
        current_curx++;
    }

    /* Update cursor pos */
    vga_set_cursor(current_curx, current_cury);

    return 0;
}

void vga_set_color(const uint8_t forcolor, const uint8_t backcolor)
{
    uint8_t current_color = (forcolor & 0x0F) | (backcolor << 4);
    return;
}

void vga_set_cursor(const uint8_t x, const uint8_t y)
{
    uint16_t pos = x + (y * 80);

    /* Send first byte */
    PORT_OUTB(0x3D4, 0x0F);
    PORT_OUTB(0x3D5, (uint8_t) (pos & 0xFF));

    /* Send second byte */
    PORT_OUTB(0x3D4, 0x0E);
    PORT_OUTB(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

int kprint(const char *str)
{
    while (*str)
    {
        vga_putc(*str);
        str++;
    }
    return 0;
}
