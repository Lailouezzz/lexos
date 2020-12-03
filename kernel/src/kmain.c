#include "lexos/boot/cpu.h"
#include "lexos/boot/gdt.h"
#include "lexos/boot/idt.h"
#include "lexos/boot/stivale2.h"
#include "lexos/boot/acpi.h"
#include "lexos/boot/apic.h"
#include "lexos/kprint.h"


void kmain(s2_struct_s *args)
{
    cpu_check();
    gdt_init();
    idt_init();

    s2_init(args);
#ifdef DEBUG
    kprint("Booted in %s mode.\n", 
            ((s2_tag_firmware_s *)s2_get_tag(S2_ID_FIRMWARE))->flags == 0 ?
            "UEFI" :
            "BIOS");
#endif
    acpi_init();
    apic_find((acpi_madt_s *)acpi_find_sdt(ACPI_MADT_SIGN));

    kprint("Successfuly started.\n");
    HALT();
}
