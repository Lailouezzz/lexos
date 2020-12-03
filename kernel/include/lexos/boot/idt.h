#ifndef H_LEXOS_BOOT_IDT
#define H_LEXOS_BOOT_IDT
#include <stdint.h>
#include <stddef.h>
#include "lexos/boot/except.h"
#include "util.h"


#define IDT_INT_GATE    0x8E
#define IDT_TRAP_GATE   0xEF
#define IDT_ENTRIES_NUM 256

#define IDT_ENTRY(off, attr, sel, _ist) \
        (idt_entry_s) \
        { \
            .offset_low16 = ((uintptr_t)off) & 0xFFFF, \
            .offset_mid16 = (((uintptr_t)off) >> 16) & 0xFFFF, \
            .offset_hig32 = (((uintptr_t)off) >> 32) & 0xFFFFFFFF, \
            \
            .type_attr = attr, \
            \
            .selector = sel, \
            \
            .ist = _ist, \
            \
            .zero = 0 \
        }


typedef struct {
    uint16_t offset_low16;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset_mid16;
    uint32_t offset_hig32;
    uint32_t zero;
} __PACKED idt_entry_s;

typedef struct  {
    uint16_t limit;
    idt_entry_s *offset;
} __PACKED idt_pointer_s;


extern idt_entry_s idt_entries[IDT_ENTRIES_NUM];
extern idt_pointer_s idt_pointer;


void idt_init(void);


#endif /// #ifndef H_LEXOS_BOOT_IDT
