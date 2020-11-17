#include "boot/stivale2.h"
#include "boot/GDT.h"
#include "tmp/kprint.h"
#include "io/port.h"


void kmain(stivale2_struct_s *arg)
{
    init_gdt();
    kprint("Hello welcome to LexOS ! :)");

    asm volatile ("hlt\n\t");
}
