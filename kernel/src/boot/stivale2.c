#include "lexos/boot/stivale2.h"


extern uint8_t stack[0x2000];


/* TAG STRUCTS */
s2_tag_rsdp_s s2_rsdp = {
    {
        .id = S2_ID_RSDP,
        .next = NULL
    },
    .rsdp = NULL
};

/* BOOT STRUCT */
__SECTION(".stivale2hdr")
s2_header_s stivale2hdr = {
    .entry_point = NULL,
    .stack = stack + sizeof(stack),
    .flags = 0,
    .tags = &s2_rsdp
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
        /* TODO : panic */
        HALT();
    }
    return;
}

s2_tag_s *s2_get_tag(uint64_t id)
{
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
