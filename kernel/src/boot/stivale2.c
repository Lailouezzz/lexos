#include "lexos/kprint.h"
#include "lexos/panic.h"

#include "lexos/boot/stivale2.h"


extern uint8_t stack[0x2000];


/*
 * TAG STRUCTS
 */

s2_tag_rsdp_s s2_rsdp = {
    {
        .id = S2_TAG_ID_RSDP,
        .next = NULL
    },
    .rsdp = NULL
};

/* BOOT HEADER */
__SECTION(".stivale2hdr")
s2_header_s stivale2hdr = {
    .entry_point = NULL,
    .stack = stack + sizeof(stack),
    .flags = 0,
    .tags = (s2_tag_s *)&s2_rsdp
};


/* Local variable */

static s2_tag_s *s2_frist_tag;


void s2_init(s2_struct_s *args)
{
    if (args != NULL)
    {
        s2_frist_tag = args->tags;
    }
    else
    {
        panic(NULL, "STIVALE2 ARGS IS NULL.\n");
    }
    return;
}

s2_tag_s *s2_find_tag(uint64_t id)
{
    if (s2_frist_tag == NULL)
    {
        panic(NULL, "FIRST TAG IS NULL PLEASE INIT BEFORE.\n");
    }

    /* Explore tags */
    s2_tag_s *cur = s2_frist_tag;
    while (cur != NULL)
    {
        if (cur->id == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void s2_print_tags(void)
{
    if (s2_frist_tag == NULL)
    {
        kprint("FIRST TAG IS NULL PLEASE INIT BEFORE.\n");
    }

    /* Explore tags */
    s2_tag_s *cur = s2_frist_tag;
    while (cur != NULL)
    {
        kprint("TAG ID : 0x%x\n", cur->id);
        cur = cur->next;
    }

    return;
}

void s2_print_mmap(void)
{
    s2_tag_mmap_s *tag_mmap = (s2_tag_mmap_s *)s2_find_tag(S2_TAG_ID_MMAP);
    if (tag_mmap == NULL)
    {
        kprint("COULD NOT FIND THE MEMORY MAP TAG.\n");
    }

    uint64_t total_mem =
            (uint64_t)tag_mmap->entries[tag_mmap->numentries-1].base +
            tag_mmap->entries[tag_mmap->numentries-1].len;
    uint64_t available_mem = 0;
    
    kprint("Total mem : %uMo.\n", total_mem/(1024*1024));

    /* Explore memory map */
    for (size_t i = 0; i < tag_mmap->numentries; i++)
    {
        kprint("Base : 0x%x ; Len : 0x%x (",
                tag_mmap->entries[i].base, tag_mmap->entries[i].len);
        switch (tag_mmap->entries[i].type)
        {
        case S2_MMAP_USABLE:
            kprint("usable");
            available_mem += tag_mmap->entries[i].len;
            break;
        case S2_MMAP_RESERVED:
            kprint("reserved");
            break;
        case S2_MMAP_ACPI_RECLAIMABLE:
            kprint("ACPI reclaimable");
            break;
        case S2_MMAP_ACPI_NVS:
            kprint("ACPI NVS");
            break;
        case S2_MMAP_BAD_MEMORY:
            kprint("bad memory");
            break;
        case S2_MMAP_BOOTLOADER_RECLAIMABLE:
            kprint("bootloader reclaimable");
            break;
        case S2_MMAP_KERNEL_AND_MODULES:
            kprint("kernel and modules");
            break;
        default:
            kprint("unknow type");
            break;
        }
        kprint(")\n");
    }

    kprint("Available mem : %uMo.\n", available_mem/(1024*1024));

    return;
}
