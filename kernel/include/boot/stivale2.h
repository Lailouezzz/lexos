#ifndef H_BOOT_STIVALE2
#define H_BOOT_STIVALE2
#include <stdint.h>
#include "util.h"


typedef struct {
    uint64_t entry_point;   // If not 0, this address will be jumped to as the
                            // entry point of the kernel.
                            // If set to 0, the ELF entry point will be used
                            // instead.

    uint64_t stack;         // This is the stack address which will be in ESP/RSP
                            // when the kernel is loaded.
                            // It can only be set to NULL for 64-bit kernels. 32-bit
                            // kernels are mandated to provide a vaild stack.
                            // 64-bit and 32-bit valid stacks must be at least 256 bytes
                            // in usable space and must be 16 byte aligned addresses.

    uint64_t flags;         // Bit 0: if 1, enable KASLR
                            // All other bits undefined

    uint64_t tags;          // Pointer to the first of the linked list of tags.
                            // see "stivale2 header tags" section.
                            // NULL = no tags.
} __PACKED stivale2_header_s;

typedef struct {
    char bootloader_brand[64];    // Bootloader null-terminated brand string
    char bootloader_version[64];  // Bootloader null-terminated version string

    uint64_t tags;          // Pointer to the first of the linked list of tags.
                            // see "stivale2 structure tags" section.
                            // NULL = no tags.
} __PACKED stivale2_struct_s;


#endif /// #ifndef H_BOOT_STIVALE2
