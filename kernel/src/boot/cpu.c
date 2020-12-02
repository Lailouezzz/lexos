#include <cpuid.h>
#include "lexos/panic.h"

#include "lexos/boot/cpu.h"


void cpu_check(void)
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;

    /* Check APIC present */
    __cpuid(0x01, a, b, c, d);
    if (!(d & (1 << 9)))
    {
        panic(NULL, "APIC IS NOT PRESENT ON THIS CPU.\n");
    }

}
