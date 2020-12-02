# Header and declarations

This section describe how write conventionnal header for LexOS.

## How header is structured

This is the structure example of headers in LexOS
(can be modified for good reason) :

```c
#ifndef H_[DIR]_[FILENAME]
#define H_[DIR]_[FILENAME]
#include <[stdheader]>
#include "[projectrelated]"
#include "[localheader]"


/* This is a comment to descript the section */

/**
 * HERE PUT THE TYPE DECLARATION (typdefs > enum > struct > typdefs) 
 */


/* This is an other comment */

/**
 * HERE PUT THE LOCAL VARIABLE (extern first)
 */


/* This is the last comment */

/**
 * HERE PUT THE FUNCTION DECLARION
 */


#endif /// #ifndef H_[DIR]_[FILENAME]

```

Note the 2 lines to separate each sections, you can put 1 line in each sections 
for separating code

---

If no comment is used you will do that :

```c
#ifndef H_[DIR]_[FILENAME]
#define H_[DIR]_[FILENAME]
#include <[stdheader]>
#include "[projectrelated]"
#include "[localheader]"


/**
 * HERE PUT THE TYPE DECLARATION (typdefs > enum > struct > typdefs) 
 */


/**
 * HERE PUT THE LOCAL VARIABLE (extern first, static last)
 */


/**
 * HERE PUT THE FUNCTION DECLARION
 */


#endif /// #ifndef H_[DIR]_[FILENAME]

```

---

## Type & name

How type & name is organized

### Type

-   `struct`        : `[name]_s`
-   `enum`          : `[name]_e`
-   `other types`   : `[name]_t`

### Name

-   No upper case (except defines)
-   Prefix local related (example : `acpi_[name]` or `idt_[name]`)

### Example

```c
#define __PACKED __attribute__((packed))

gdt_entry_s gdt_entries[3];

extern gdt_entry_s gdt_entries[3];

void vga_text_return(void);

void idt_init(void);

typedef struct {
    uint16_t offset_low16;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset_mid16;
    uint32_t offset_hig32;
    uint32_t zero;
} __PACKED idt_entry_s;
```

## TODO

-   Source convention
-   Source tree convention
-   Use the idea of a libk or delete this ?
