#ifndef H_LEXOS_BOOT_IDT
#define H_LEXOS_BOOT_IDT
#include <stdint.h>
#include <stddef.h>
#include "lexos/boot/except.h"
#include "util.h"


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
    uint64_t offset;
} __PACKED idt_pointer_s;


extern idt_entry_s idt_entries[256];
extern idt_pointer_s idt_pointer;


void idt_init(void);


#endif /// #ifndef H_LEXOS_BOOT_IDT
