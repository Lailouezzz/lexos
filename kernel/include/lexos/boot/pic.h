#ifndef H_LEXOS_BOOT_PIC
#define H_LEXOS_BOOT_PIC
#include <stdint.h>
#include <stddef.h>
#include "lexos/asm/ioport.h"
#include "util.h"


/* Define PIC constant */

#define PIC_MPORT_C     0x0020
#define PIC_MPORT_D     0x0021
#define PIC_SPORT_C     0x00A0
#define PIC_SPORT_D     0x00A1

#define PIC_EOI         0x20

/* Remap offset */

#define PIC_MIRQ_OFF    0x20
#define PIC_SIRQ_OFF    0x28


void pic_remap(void);
void pic_disable(void);


#endif /// #ifndef H_LEXOS_BOOT_PIC
