#include "lexos/boot/acpi.h"
#include "lexos/kprint.h"


/* Local variable */

acpi_rsdp_s *acpi_rsdp_ptr = NULL;


acpi_rsdp_s *acpi_find_rsdp(void)
{
    void *ebda_baseaddr = (void *)BIOS_EBDA_BASEADDR; /* Already 16 bytes aligned */
    
    /* Search RSDP in the first 1KB of EBDA in 16 bytes boundaries */
    for (size_t off = 0; off < 1024; off += 16)
    {
        if (memcmp(ebda_baseaddr+off, ACPI_RSDP_SIGN, 8) == 0)
        {
            return ebda_baseaddr+off;
        }
    }

    /* Search RSDP in memory region from 0x000E0000 to 0x000FFFFF */
    for (void *it = (void *)0x000E0000; it < (void *)0x000FFFFF; it += 16)
    {
        if (memcmp(it, ACPI_RSDP_SIGN, 8) == 0)
        {
            return it;
        }
    }

    return NULL;
}

void acpi_init(void)
{
    acpi_rsdp_ptr = acpi_find_rsdp();
    if (!acpi_rsdp_ptr)
    {
        /* TODO : PANIC */
        kprint("PANIC : could not find RSDP.\n");
        HALT();
    }


}
