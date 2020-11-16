#include "boot/stivale2.h"
#include "boot/GDT.h"


void kmain(stivale2_struct_s *arg)
{
    init_gdt();
    ((char *)0xB8000)[0] = 'H';
    ((char *)0xB8000)[2] = 'e';
    ((char *)0xB8000)[4] = 'l';
    ((char *)0xB8000)[6] = 'l';
    ((char *)0xB8000)[8] = 'o';

    asm volatile ("hlt\n\t");
}
