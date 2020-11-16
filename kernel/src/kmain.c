#include "boot/GDT.h"


void kmain(void)
{
    init_gdt();
    for(;;) ;
}
