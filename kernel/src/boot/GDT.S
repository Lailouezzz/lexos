extern gdt_pointer
global init_gdt

bits 64
section .text

; void init_gdt(void)
init_gdt:
    ; load gdtr register
    lgdt [gdt_pointer]

    ; update segments
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
    ;jmp 0x08:.flush
.flush:
    ret