#include "lexos/boot/stivale2.h"
#include "lexos/kprint.h"
#include "lexos/panic.h"
#include "lexos/string.h"

#include "lexos/boot/acpi.h"


/* Local variable */

static acpi_rsdp_s *acpi_rsdp = NULL;
static acpi_rsdp2_s *acpi_rsdp2 = NULL;


/* Private function */

acpi_sdt_header_s *acpi_find_sdt_with_rsdt(uint32_t sign);
acpi_sdt_header_s *acpi_find_sdt_with_xsdt(uint32_t sign);


int acpi_checksum(const void *ptr, size_t size)
{
    unsigned char sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum += ((const char *) ptr)[i];
    }
    return (sum == 0);
}

void acpi_init()
{
    s2_tag_rsdp_s *tag_rsdp = ((s2_tag_rsdp_s *)s2_find_tag(S2_ID_RSDP));

    if (!tag_rsdp)
    {
        panic(NULL, "COULD NOT FIND STIVALE2 TAG RSDP.\n");
    }

    acpi_rsdp = tag_rsdp->rsdp;
    if (!acpi_rsdp)
    {
        panic(NULL, "COULD NOT FIND RSDP.\n");
    }

    kprint("ACPI version %s.\n", acpi_rsdp->rev == 0 ? "1.0" : "2.0 to 6.1");
    
    /* If ACPI version == 2 use rsdp2 */
    if (acpi_rsdp->rev == 2)
    {
        acpi_rsdp2 = (acpi_rsdp2_s *)acpi_rsdp;
        acpi_rsdp = NULL;
    }


    if (acpi_rsdp2)
    {
        /* Check RSDP2 */
        if (!acpi_checksum(acpi_rsdp2, sizeof(*acpi_rsdp2)))
        {
            panic(NULL, "RSDP2 CHECKSUM INVALID.\n");
        }

        /* Check XSDT */
        if (!acpi_checksum(acpi_rsdp2->pxsdt,
                acpi_rsdp2->pxsdt->header.len))
        {
            panic(NULL, "XSDT CHECKSUM INVALID.\n");
        }
    }
    else
    {
        /* Check RSDP */
        if (!acpi_checksum(acpi_rsdp, sizeof(*acpi_rsdp)))
        {
            panic(NULL, "RSDP CHECKSUM INVALID.\n");
        }

        /* Check RSDT */
        if (!acpi_checksum((acpi_rsdt_s *)((uintptr_t)acpi_rsdp->prsdt),
                ((acpi_rsdt_s *)((uintptr_t)acpi_rsdp->prsdt))->header.len))
        {
            panic(NULL, "RSDT CHECKSUM INVALID.\n");
        }
    }

    return;
}

acpi_sdt_header_s *acpi_find_sdt_with_rsdt(uint32_t sign)
{
    acpi_rsdt_s *rsdt = (acpi_rsdt_s *)((uintptr_t)acpi_rsdp->prsdt);

    if (sign == ACPI_RSDT_SIGN)
    {
        /* To be sure */
        return *((uint32_t *)rsdt->header.sign) == sign ?
                (acpi_sdt_header_s *)((uintptr_t)acpi_rsdp->prsdt) :
                NULL;
    }

    size_t numentries =
            (rsdt->header.len - sizeof(rsdt->header)) / sizeof(rsdt->other);
    uint32_t *other = &rsdt->other;

    for (size_t i = 0; i < numentries; i++)
    {
        if (*((uint32_t *)((acpi_sdt_header_s *)((uintptr_t)other[i]))->sign)
                == sign)
        {
            return (acpi_sdt_header_s *)((uintptr_t)other[i]);
        }
    }

    return NULL;
}

acpi_sdt_header_s *acpi_find_sdt_with_xsdt(uint32_t sign)
{
    acpi_xsdt_s *xsdt = acpi_rsdp2->pxsdt;

    if (sign == ACPI_XSDT_SIGN)
    {
        /* To be sure */
        return *((uint32_t *)xsdt->header.sign) == sign ?
                (acpi_sdt_header_s *)xsdt :
                NULL;
    }

    size_t numentries =
            (xsdt->header.len - sizeof(xsdt->header)) / sizeof(xsdt->other);
    acpi_sdt_header_s **other = &xsdt->other;

    for (size_t i = 0; i < numentries; i++)
    {
        if (*((uint32_t *)other[i]->sign) == sign)
        {
            return other[i];
        }
    }

    return NULL;
}

acpi_sdt_header_s *acpi_find_sdt(uint32_t sign)
{
    if (acpi_rsdp2)
    {
        return acpi_find_sdt_with_xsdt(sign);
    }
    else if (acpi_rsdp)
    {
        return acpi_find_sdt_with_rsdt(sign);
    }
    else
    {
        panic(NULL, "NO RSDP OR RSDP2 FOUND.\n");
    }
}
