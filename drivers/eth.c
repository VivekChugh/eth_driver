
#include "eth.h"

#define ETH_BASE 0x40028000

typedef struct
{
    volatile uint32_t desc0;
    volatile uint32_t desc1;
    volatile uint32_t buf1;
    volatile uint32_t buf2;
} eth_dma_desc_t;

static eth_dma_desc_t rx_desc[ETH_RX_DESC_CNT];
static eth_dma_desc_t tx_desc[ETH_TX_DESC_CNT];

static uint8_t rx_buf[ETH_RX_DESC_CNT][1536];
static uint8_t tx_buf[ETH_TX_DESC_CNT][1536];

static uint32_t rx_index = 0;
static uint32_t tx_index = 0;

static void eth_dma_init()
{
    for(int i=0;i<ETH_RX_DESC_CNT;i++)
    {
        rx_desc[i].buf1 = (uint32_t)&rx_buf[i];
        rx_desc[i].desc0 = 0x80000000;
    }

    for(int i=0;i<ETH_TX_DESC_CNT;i++)
    {
        tx_desc[i].buf1 = (uint32_t)&tx_buf[i];
    }
}

#ifdef SIMULATION
static uint32_t sim_MACCR = 0;
static uint32_t sim_DMAOMR = 0;
#endif

void eth_init(void)
{
    eth_dma_init();

#ifdef SIMULATION
    volatile uint32_t *MACCR = &sim_MACCR;
    volatile uint32_t *DMAOMR = &sim_DMAOMR;
#else
    volatile uint32_t *MACCR = (uint32_t*)(ETH_BASE + 0x0000);
    volatile uint32_t *DMAOMR = (uint32_t*)(ETH_BASE + 0x1018);
#endif

    *MACCR |= (1<<2);
    *MACCR |= (1<<3);

    *DMAOMR |= (1<<1);
    *DMAOMR |= (1<<13);
}

void eth_poll_rx(void)
{
    eth_dma_desc_t *desc = &rx_desc[rx_index];

    if(!(desc->desc0 & 0x80000000))
    {
        uint8_t *packet = (uint8_t*)desc->buf1;

        (void)packet;

        desc->desc0 |= 0x80000000;

        rx_index = (rx_index + 1) % ETH_RX_DESC_CNT;
    }
}

void eth_send(uint8_t *buf, uint32_t len)
{
    eth_dma_desc_t *desc = &tx_desc[tx_index];

    for(uint32_t i=0;i<len;i++)
        tx_buf[tx_index][i] = buf[i];

    desc->desc1 = len;
    desc->desc0 = 0x80000000;

    tx_index = (tx_index + 1) % ETH_TX_DESC_CNT;
}
