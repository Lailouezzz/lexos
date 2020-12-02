#include "lexos/boot/stivale2.h"
#include "lexos/boot/cpu.h"
#include "lexos/boot/gdt.h"
#include "lexos/boot/idt.h"
#include "lexos/boot/acpi.h"
#include "lexos/kprint.h"


void kmain(s2_struct_s *args)
{
    s2_init(args);
    cpu_check();
    gdt_init();
    idt_init();
    acpi_init(((s2_tag_rsdp_s *)s2_get_tag(S2_ID_RSDP))->rsdp);


    kprint("Successfuly started.\n");
    HALT();
}
