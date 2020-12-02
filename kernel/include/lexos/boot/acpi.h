#ifndef H_LEXOS_BOOT_ACPI
#define H_LEXOS_BOOT_ACPI
#include <stdint.h>
#include <stddef.h>
#include "lexos/string.h"
#include "util.h"


#define BIOS_EBDA_BASEADDR ((void *)((uintptr_t) \
        (*((uint16_t *)0x040E) << 4) \
        )) 
#define ACPI_RSDP_SIGN "RSD PTR "


typedef struct {
    uint8_t sign[8];
    uint8_t checksum;
    uint8_t OEMID[6];
    uint8_t rev;
    uint32_t prsdt;
} __PACKED acpi_rsdp_s;

typedef struct {
    acpi_rsdp_s firstpart;
    uint32_t len;
    void *pxsdt;    /* TODO : replace void * by the struct */
    uint8_t extchecksum;
    uint8_t reserved[3];
} __PACKED acpi_rsdp2_desc_s;


/* Init the acpi driver */
void acpi_init(acpi_rsdp_s *rsdp);


#endif /// #ifndef H_LEXOS_BOOT_ACPI
