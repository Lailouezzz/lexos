#include "lexos/kprint.h"
#include "lexos/panic.h"

#include "lexos/arch/apic.h"


/* Local variable */

static volatile uint32_t *lapic = NULL;
static volatile uint32_t *ioapic = NULL;


void apic_find(acpi_madt_s *madt)
{
    if (!madt)
    {
        panic(NULL, "MADT POINTER IS NULL.\n");
    }

    lapic = (uint32_t *)((uintptr_t)madt->plapic);

    acpi_madt_rec_s *cur = &madt->records;
    while (((uintptr_t)cur - (uintptr_t)madt) < madt->header.len
            && cur->len != 0) /* Prevent infinite loop */
    {
        acpi_madt_plapic_s *cur_plapic;
        acpi_madt_ioapic_s *cur_ioapic;
        acpi_madt_lapicaddr_s *cur_lapicaddr;

        switch (cur->type)
        {
        case ACPI_MADT_REC_PLAPIC:
            cur_plapic = (acpi_madt_plapic_s *)cur;
            kprint("Processor LAPIC (cpu : %u, apic_id : %u, flags : 0x%x)\n",
                    cur_plapic->proc_id, cur_plapic->apic_id,
                    cur_plapic->flags);
            break;
        case ACPI_MADT_REC_IOAPIC:
            cur_ioapic = (acpi_madt_ioapic_s *)cur;
            kprint("I/O APIC (id : %u, addr : 0x%x)\n", cur_ioapic->ioapic_id,
                    cur_ioapic->pioapic);

            ioapic = (uint32_t *)((uintptr_t)cur_ioapic->pioapic);
            break;
        case ACPI_MADT_REC_LAPICADDR:
            cur_lapicaddr = (acpi_madt_lapicaddr_s *)cur;
            kprint("LAPIC override address : 0x%x\n", cur_lapicaddr->plapic);

            lapic = cur_lapicaddr->plapic;
            break;
        case ACPI_MADT_REC_ISO:
        case ACPI_MADT_REC_NMI:
            /* Nothing to do */
            break;
        default:
            kprint("Unreconized madt rec entry type (type : %u)\n", cur->type);
            break;
        }
        cur = (void *)cur + cur->len;
    }
    
    return;
}
