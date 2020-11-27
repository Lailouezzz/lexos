#include <stdint.h>
#include <cpuid.h>
#include "tmp/kprint.h"


/* 
 * This routine check cpu capability
 */
void check_cpu(void)
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;

    /* Check APIC present */
    __cpuid(0x01, a, b, c, d);
    if (d & (1 << 9))
    {
        kprint("CPU has APIC.\n");
    }
    if (c & (1 << 21))
    {
        kprint("CPU has x2APIC.\n");
    }

}
