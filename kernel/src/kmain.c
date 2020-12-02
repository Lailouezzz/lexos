#include "lexos/boot/cpu.h"
#include "lexos/boot/gdt.h"
#include "lexos/boot/idt.h"
#include "lexos/boot/stivale2.h"
#include "lexos/boot/acpi.h"
#include "lexos/kprint.h"


void kmain(s2_struct_s *args)
{
    cpu_check();
    gdt_init();
    idt_init();

    s2_init(args);
#ifdef DEBUG
    s2_tag_s *cur = args->tags;
    while (cur != NULL)
    {
        kprint("TAG ID : 0x%x\n", cur->id);
        cur = cur->next;
    }
    kprint("Booted in %s mode.\n", 
            ((s2_tag_firmware_s *)s2_get_tag(S2_ID_FIRMWARE))->flags == 0 ?
            "UEFI" :
            "BIOS");
#endif
    acpi_init();

    kprint("Successfuly started.\n");
    HALT();
}
