#include "lexos/boot/stivale2.h"
#include "lexos/kprint.h"

#include "lexos/boot/acpi.h"


/* Local variable */

static acpi_rsdp_s *acpi_rsdp_ptr = NULL;


void acpi_init()
{
    acpi_rsdp_ptr = ((s2_tag_rsdp_s *)s2_get_tag(S2_ID_RSDP))->rsdp;
    if (!acpi_rsdp_ptr)
    {
        /* TODO : PANIC */
        kprint("PANIC : could not find RSDP.\n");
        HALT();
    }


}
