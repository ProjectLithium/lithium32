#include "pit.h"
#include <drivers/devices/irq.h>

uint16_t ticks = 0;

void pit_handler(regdump* regs)
{
    ticks++;
    if (ticks >= 65536)
        ticks = 0;
}

void pit_init()
{
    irq_register_handler(0, pit_handler);
}

uint16_t pit_get_time()
{
    return ticks;
}