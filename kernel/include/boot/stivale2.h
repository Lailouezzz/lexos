#ifndef H_BOOT_STIVALE2
#define H_BOOT_STIVALE2


struct stivale2_header {
    unsigned long entry_point;   // If not 0, this address will be jumped to as the
                            // entry point of the kernel.
                            // If set to 0, the ELF entry point will be used
                            // instead.

    unsigned long stack;    // This is the stack address which will be in ESP/RSP
                            // when the kernel is loaded.
                            // It can only be set to NULL for 64-bit kernels. 32-bit
                            // kernels are mandated to provide a vaild stack.
                            // 64-bit and 32-bit valid stacks must be at least 256 bytes
                            // in usable space and must be 16 byte aligned addresses.

    unsigned long flags;    // Bit 0: if 1, enable KASLR
                            // All other bits undefined

    unsigned long tags;     // Pointer to the first of the linked list of tags.
                            // see "stivale2 header tags" section.
                            // NULL = no tags.
} __attribute__((packed));


#endif /// #ifndef H_BOOT_STIVALE2
