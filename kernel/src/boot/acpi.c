#include "lexos/boot/acpi.h"
#include "lexos/kprint.h"


/* Local variable */

static acpi_rsdp_s *acpi_rsdp_ptr = NULL;


void acpi_init(acpi_rsdp_s *rsdp)
{
    acpi_rsdp_ptr = rsdp;
    if (!acpi_rsdp_ptr)
    {
        /* TODO : PANIC */
        kprint("PANIC : could not find RSDP.\n");
        HALT();
    }


}
