ENTRY(kmain)

SECTIONS
{
    . = 0xffffffff80000000;
    virtualaddr = .;

    .stivale2hdr ALIGN(4K) :
    {
        KEEP(*(.stivale2hdr))
    }

    .text ALIGN(4K) :
    {
        KEEP(*(.text*))
    }

    .data ALIGN(4K) :
    {
        KEEP(*(.text*))
    }

    .bss ALIGN(4K) :
    {
        KEEP(*(.text*))
    }
}
