#include "lexos/boot/stivale2.h"
#include "lexos/panic.h"

#include "lexos/boot/acpi.h"


/* Local variable */

static acpi_rsdp_s *acpi_rsdp = NULL;


void acpi_init()
{
    s2_tag_rsdp_s *tag_rsdp = ((s2_tag_rsdp_s *)s2_get_tag(S2_ID_RSDP));
    if (!tag_rsdp)
    {
        panic(NULL, "COULD NOT FIND RSDP.\n");
    }
    acpi_rsdp = tag_rsdp->rsdp;


}
