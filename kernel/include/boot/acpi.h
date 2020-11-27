#ifndef H_BOOT_ACPI
#define H_BOOT_ACPI
#include <stdint.h>
#include "util.h"


#define BIOS_ADDR_EBDA_BASEADDR 0x040E
#define ACPI_RSDP_SIGN "RSD PTR "


typedef struct {
    uint8_t sign[8];
    uint8_t checksum;
    uint8_t OEMID[6];
    uint8_t rev;
    uint32_t prsdt;
} __PACKED rsdp_desc;

typedef struct {
    uint32_t len;
    uint64_t pxsdt;
    uint8_t extchecksum;
    uint8_t reserved[3];
} __PACKED rsdp2_desc;


/* Return pointer to the rsdp descriptor */
rsdp_desc *acpi_find_rsdp(void);


#endif /// #ifndef H_BOOT_ACPI
