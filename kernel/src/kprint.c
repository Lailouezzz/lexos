#include "lexos/kprint.h"


/* Local variable */

static uint8_t current_curx = 0;
static uint8_t current_cury = 0;
static uint8_t current_color = 0x0F; /* forgroud : white | background : black */


int vga_text_putc(const char c)
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
    vga_text_set_cursor(current_curx, current_cury);

    return 0;
}

void vga_text_set_color(const uint8_t forcolor, const uint8_t backcolor)
{
    current_color = (forcolor & 0x0F) | (backcolor << 4);
    return;
}

void vga_text_set_cursor(const uint8_t x, const uint8_t y)
{
    uint16_t pos = x + (y * 80);

    /* Send first byte */
    PORT_OUTB(0x3D4, 0x0F);
    PORT_OUTB(0x3D5, (uint8_t) (pos & 0xFF));

    /* Send second byte */
    PORT_OUTB(0x3D4, 0x0E);
    PORT_OUTB(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void vga_text_return(void)
{
    current_cury++;
    current_curx = 0;
    vga_text_set_cursor(current_curx, current_cury);
}

int kvprint(const char *fmt, va_list args)
{

    while (1)
    {
        /* *
         *  x : for hex value
         *  u : for unsigned value
         *  d : for decimal value
         *  s : for string
         *  c : for char
         * */
        if(*fmt == '%')
        {
            fmt++;
            const char *str = 0;
            char c = 0;
            int d = 0;
            unsigned int u = 0;
            uint64_t x = 0;

            char buf[64] = {0};
            int i;
            int sign;
            switch (*fmt)
            {
            case 's':
                str = va_arg(args, const char *);
                while (*str)
                {
                    vga_text_putc(*str++);
                }
                break;
            case 'c':
                c = (char) va_arg(args, int);
                vga_text_putc(c);
                break;
            case 'd':
                d = va_arg(args, int);
                i = 0;
                sign = d < 0;
                d = sign?-d:d;
                do
                {
                    buf[i] = (d % 10) + '0';
                    d /= 10;
                    i++;
                } while (d != 0);
                if (sign)
                {
                    buf[i++] = '-';
                }
                while (--i >= 0)
                {
                    vga_text_putc(buf[i]);
                }
                break;
            case 'u':
                u = va_arg(args, unsigned int);
                i = 0;
                do
                {
                    buf[i] = (u % 10) + '0';
                    u /= 10;
                    i++;
                } while (u != 0);
                while (--i >= 0)
                {
                    vga_text_putc(buf[i]);
                }
                break;
            case 'x':
                x = va_arg(args, uint64_t);
                for (i = 0; i < 8*2; i++)
                {
                    buf[i] = (x % 16) <= 9 ? 
                            (x % 16) + '0' : 
                            (x % 16) + 'A' - 10;
                    x /= 16;
                }
                while (--i >= 0)
                {
                    vga_text_putc(buf[i]);
                }
                break;
            default:

                break;
            }
            fmt++;
            continue;
        }

        if(!*fmt)
        {
            break;
        }

        /* special and normal char */
        switch (*fmt)
        {
        case '\n':
            vga_text_return();
            fmt++;
            break;
        case '\t':
            /* TODO : implement tab */
            break;
        default:
            vga_text_putc(*fmt++);
            break;
        }
    }
    return 0;
}

int kprint(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    kvprint(fmt, args);
    va_end(args);
    return 0;
}
