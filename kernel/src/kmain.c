#include "boot/stivale2.h"
#include "boot/GDT.h"
#include "tmp/kprint.h"
#include "io/port.h"

extern void kernel_virt_offset;
extern void kernel_end;

void kmain(stivale2_struct_s *arg)
{
    init_gdt();
    kprint("KERNEL START : 0x%x\n", &kernel_virt_offset);
    kprint("KERNEL END :   0x%x\n", &kernel_end);

    asm volatile ("hlt\n\t");
}
