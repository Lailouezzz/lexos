#ifndef H_LEXOS_ARCH_APIC
#define H_LEXOS_ARCH_APIC
#include <stdint.h>
#include <stddef.h>
#include "lexos/boot/acpi.h"
#include "util.h"


void apic_find(acpi_madt_s *madt);


#endif /// #ifndef H_LEXOS_ARCH_APIC
