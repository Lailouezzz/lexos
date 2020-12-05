#ifndef H_LEXOS_BOOT_STIVALE2
#define H_LEXOS_BOOT_STIVALE2
#include <stdint.h>
#include <stddef.h>
#include "lexos/boot/acpi.h"
#include "util.h"


/*
 * Define stivale2 tag identifiers
 */

#define S2_TAG_ID_RSDP      0x9e1786930a375e78
#define S2_TAG_ID_FIRMWARE  0x359d837855e3858c
#define S2_TAG_ID_MMAP      0x2187f79e8612de07

/* Map entry type */
#define S2_MMAP_USABLE                  1
#define S2_MMAP_RESERVED                2
#define S2_MMAP_ACPI_RECLAIMABLE        3
#define S2_MMAP_ACPI_NVS                4
#define S2_MMAP_BAD_MEMORY              5
#define S2_MMAP_BOOTLOADER_RECLAIMABLE  0x1000
#define S2_MMAP_KERNEL_AND_MODULES      0x1001


/*
 * Define stivale2 tags
 */

/* Primitive */
typedef struct {
    uint64_t id;
    void *next;
} __PACKED s2_tag_s;

typedef struct {
    s2_tag_s base;
    acpi_rsdp_s *rsdp;      // Pointer to the RSDP
} __PACKED s2_tag_rsdp_s;

typedef struct {
    s2_tag_s base;
    uint64_t flags;         // Bit 0: 0 = UEFI, 1 = BIOS
} __PACKED s2_tag_firmware_s;

/* Map entry */
typedef struct {
    void *base;
    uint64_t len;
    uint32_t type; /* S2_MMAP_**** */
    uint32_t unused;
} __PACKED s2_mmap_entry_s;

typedef struct {
    s2_tag_s base;
    uint64_t numentries;
    s2_mmap_entry_s entries[];
} __PACKED s2_tag_mmap_s;

/* Boot struct */
typedef struct {
    char bootloader_brand[64];    // Bootloader null-terminated brand string
    char bootloader_version[64];  // Bootloader null-terminated version string

    s2_tag_s *tags;         // Pointer to the first of the linked list of tags.
                            // see "stivale2 structure tags" section.
                            // NULL = no tags.
} __PACKED s2_struct_s;

/* Principal header */
typedef struct {
    void *entry_point;      // If not 0, this address will be jumped to as the
                            // entry point of the kernel.
                            // If set to 0, the ELF entry point will be used
                            // instead.

    void *stack;            // This is the stack address which will be in ESP/RSP
                            // when the kernel is loaded.
                            // It can only be set to NULL for 64-bit kernels. 32-bit
                            // kernels are mandated to provide a vaild stack.
                            // 64-bit and 32-bit valid stacks must be at least 256 bytes
                            // in usable space and must be 16 byte aligned addresses.

    uint64_t flags;         // Bit 0: if 1, enable KASLR
                            // All other bits undefined

    s2_tag_s *tags;         // Pointer to the first of the linked list of tags.
                            // see "stivale2 header tags" section.
                            // NULL = no tags.
} __PACKED s2_header_s;


/* Init stivale2 local variables */
void s2_init(s2_struct_s *args);
/* Return stivale2 tag ptr if tag find, NULL if not */
s2_tag_s *s2_find_tag(uint64_t id);

/* TODO : delete s2_print_*** function */

/* Print all avaible tags */
void s2_print_tags(void);
/* Print memory map */
void s2_print_mmap(void);


#endif /// #ifndef H_LEXOS_BOOT_STIVALE2
