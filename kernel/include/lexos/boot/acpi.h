#ifndef H_LEXOS_BOOT_ACPI
#define H_LEXOS_BOOT_ACPI
#include <stdint.h>
#include <stddef.h>
#include "util.h"


/*
 * ACPI tables sign
 */

#define ACPI_RSDT_SIGN D_CHR('R', 'S', 'D', 'T')
#define ACPI_XSDT_SIGN D_CHR('X', 'S', 'D', 'T')
#define ACPI_MADT_SIGN D_CHR('A', 'P', 'I', 'C')
#define ACPI_FADT_SIGN D_CHR('F', 'A', 'C', 'P')

/*
 * MADT
 */

#define ACPI_MADT_REC_PLAPIC    ((uint8_t)0)
#define ACPI_MADT_REC_IOAPIC    ((uint8_t)1)
#define ACPI_MADT_REC_ISO       ((uint8_t)2)
#define ACPI_MADT_REC_NMI       ((uint8_t)4)
#define ACPI_MADT_REC_LAPICADDR ((uint8_t)5)


/* Header of each table */

typedef struct {
    uint8_t sign[4];
    uint32_t len;
    uint8_t rev;
    uint8_t checksum;
    uint8_t OEMID[6];
    uint8_t OEMTABLEID[8];
    uint32_t OEM_rev;
    uint32_t creator_id;
    uint32_t creator_rev;
} __PACKED acpi_sdt_header_s;

/*
 * Various ACPI TABLE
 */

/* MADT */

typedef struct {
    uint8_t type;
    uint8_t len;
} __PACKED acpi_madt_rec_s;

typedef struct {
    acpi_madt_rec_s header;
    uint8_t proc_id;
    uint8_t apic_id;
    uint32_t flags; /* (bit 0 = Processor Enabled) (bit 1 = Online Capable) */
} __PACKED acpi_madt_plapic_s;

typedef struct {
    acpi_madt_rec_s header;
    uint8_t ioapic_id;
    uint8_t reserved;
    uint32_t pioapic;
    uint32_t globintbase; /* Global System Interrupt Base */
} __PACKED acpi_madt_ioapic_s;

typedef struct {
    acpi_madt_rec_s header;
    uint8_t bus_src;
    uint8_t irq_src;
    uint32_t globsysint; /* Global System Interrupt */
    uint16_t flags;
} __PACKED acpi_madt_iso_s; /* Interrupt source override */

typedef struct {
    acpi_madt_rec_s header;
    uint8_t proc_id; /* 0xFF mean all processors local apic */
    uint16_t flags;
    uint8_t lint;
} __PACKED acpi_madt_nmi_s;

typedef struct {
    acpi_madt_rec_s header;
    uint32_t *plapic;
} __PACKED acpi_madt_lapicaddr_s; /* Local APIC Address Override */

typedef struct {
    acpi_sdt_header_s header;
    uint32_t plapic;
    uint32_t flags;
    acpi_madt_rec_s records;
} __PACKED acpi_madt_s; /* USE header.len NOT sizeof */

/*
 * RSDT and XSDT
 */

typedef struct {
    acpi_sdt_header_s header;
    uint32_t other;     /* (&other)[i] to iterate (cast in acpi_sdt_header_s) */
} __PACKED acpi_rsdt_s; /* USE header.len NOT sizeof */

typedef struct {
    acpi_sdt_header_s header;
    acpi_sdt_header_s *other;   /* (&other)[i] to iterate */
} __PACKED acpi_xsdt_s; /* USE header.len NOT sizeof */

/*
 * RSDP for ACPI version 1.0 and >= 2.0
 */

typedef struct {
    uint8_t sign[8];
    uint8_t checksum;
    uint8_t OEMID[6];
    uint8_t rev;
    uint32_t prsdt;     /* Must be casted in (acpi_rsdt_s *) */
} __PACKED acpi_rsdp_s;

typedef struct {
    acpi_rsdp_s firstpart;
    uint32_t len;
    acpi_xsdt_s *pxsdt;
    uint8_t extchecksum;
    uint8_t reserved[3];
} __PACKED acpi_rsdp2_s;


/* != 0 if checksum is okey ; == 0 if checksum error */
int acpi_checksum(const void *ptr, size_t size);
/* Init the ACPI */
void acpi_init(void);
/* Return desired SDT */
acpi_sdt_header_s *acpi_find_sdt(uint32_t sign);


#endif /// #ifndef H_LEXOS_BOOT_ACPI
