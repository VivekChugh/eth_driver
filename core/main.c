
#include "eth.h"
#include "phy.h"

int main(void)
{
    eth_init();
    phy_init();

    while (1)
    {
        eth_poll_rx();
    }
}
