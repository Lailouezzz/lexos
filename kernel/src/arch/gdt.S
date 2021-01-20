extern gdt_pointer
global gdt_init


bits 64
section .text


; void gdt_init(void)
gdt_init:
    ; load gdtr register
    lgdt [gdt_pointer]

    
    ; switch to 0x08 CS
    push QWORD 0x08
    push QWORD .flush
    retfq
.flush:

    ; update segments
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
    retq
