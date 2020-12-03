#include "lexos/boot/cpu.h"
#include "lexos/boot/gdt.h"
#include "lexos/boot/idt.h"
#include "lexos/boot/stivale2.h"
#include "lexos/boot/acpi.h"
#include "lexos/boot/pic.h"
#include "lexos/boot/apic.h"
#include "lexos/kprint.h"


void kmain(s2_struct_s *args)
{
    cpu_check();
    gdt_init();
    idt_init();
    s2_init(args);

    pic_remap();
    acpi_init();
    apic_find((acpi_madt_s *)acpi_find_sdt(ACPI_MADT_SIGN));

    kprint("Successfuly started.\n");
    HALT();
}
