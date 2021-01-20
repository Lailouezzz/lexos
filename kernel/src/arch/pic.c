#include "lexos/arch/pic.h"


void pic_remap(void)
{
    uint8_t m1, m2;
 
	m1 = PORT_INB(PIC_MPORT_D);
	m2 = PORT_INB(PIC_SPORT_D);

    PORT_OUTB(PIC_MPORT_C, 0x11);
    PORT_OUTB(PIC_SPORT_C, 0x11);

    IO_WAIT();

    PORT_OUTB(PIC_MPORT_D, PIC_MIRQ_OFF);
    PORT_OUTB(PIC_SPORT_D, PIC_SIRQ_OFF);

    IO_WAIT();

    PORT_OUTB(PIC_MPORT_D, 4);
    PORT_OUTB(PIC_SPORT_D, 2);

    IO_WAIT();
    
    PORT_OUTB(PIC_MPORT_D, m1);
    PORT_OUTB(PIC_SPORT_D, m2);

    return;
}

void pic_disable(void)
{
    PORT_OUTB(PIC_MPORT_D, 0xFF);
    PORT_OUTB(PIC_SPORT_D, 0xFF);

    return;
}
