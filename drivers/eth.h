
#ifndef ETH_H
#define ETH_H

#include <stdint.h>

#define ETH_RX_DESC_CNT 8
#define ETH_TX_DESC_CNT 8

void eth_init(void);
void eth_poll_rx(void);
void eth_send(uint8_t *buf, uint32_t len);

#endif
