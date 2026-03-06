
#include "phy.h"
#include <stdint.h>

#define MDIO_BASE 0x40028000

static void mdio_write(uint8_t reg, uint16_t value)
{
    volatile uint32_t *MDIO = (uint32_t*)(MDIO_BASE + 0x20);
    *MDIO = (reg << 16) | value;
}

static uint16_t mdio_read(uint8_t reg)
{
    volatile uint32_t *MDIO = (uint32_t*)(MDIO_BASE + 0x20);
    return (*MDIO >> 16);
}

void phy_init(void)
{
    mdio_write(0x00, 0x8000);
}

int phy_link_up(void)
{
    uint16_t status = mdio_read(1);
    return (status & (1<<2));
}
