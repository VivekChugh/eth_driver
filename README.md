# Ethernet DMA Driver

This repository contains a lightweight Ethernet driver implementation for an ARM Cortex-M7 microcontroller. The code demonstrates the use of DMA descriptors for transmit and receive operations along with a simple PHY interface. It is intended for educational purposes and as a starting point for embedded networking projects.

---

## Repository Structure

```
eth_dma_driver/
├── Makefile             # Build rules for host and QEMU simulation
├── README.md            # This file
├── core/
│   ├── linker.ld        # Linker script for the target
│   ├── main.c           # Application entry point
│   └── startup.s        # Cortex-M7 startup assembly
└── drivers/
    ├── eth.c            # Ethernet MAC + DMA driver
    ├── eth.h            # Ethernet driver API
    ├── phy.c            # PHY MDIO interface
    └── phy.h            # PHY driver API
```

## Features

- Basic Ethernet MAC initialization using memory-mapped registers
- DMA descriptor ring buffers for TX/RX
- Simple polling-based receive handling
- PHY initialization and link status check via MDIO
- Simulation support via `SIMULATION` build flag

## Requirements

- `arm-none-eabi-gcc` toolchain (tested with GCC 10+)
- `qemu-system-arm` (for running the software in simulation)

> **Note:** The code is bare-metal and does not depend on any standard C library.

## Building

To compile the firmware for the target board:

```sh
make
```

The resulting binary image will be written to `eth_driver` (ELF: `eth_driver.elf`).

To build a simulated version (uses stubbed registers):

```sh
make sim
```

This produces `eth_driver_sim` and an ELF image built with `-D SIMULATION`.

## Running in QEMU

If you have `qemu-system-arm` installed, you can run the simulated build with:

```sh
make run_sim
```

The virtual board is configured as an STM32VLDISCOVERY and will execute the firmware without a graphical display (`-nographic`).

## Usage

In a real system the firmware initializes the Ethernet MAC and PHY on startup. The `main` loop currently polls for received frames:

```c
eth_init();
phy_init();

while (1) {
    eth_poll_rx();
}
```

The `eth_send()` function can be used to transmit packets, and `phy_link_up()` queries the link status.

## Extending the Driver

- Add interrupt support to replace polling
- Implement buffer management and packet parsing
- Support more PHY registers and auto-negotiation
- Integrate with a lightweight IP stack (e.g. lwIP)

---

Feel free to adapt or expand this driver for your own hardware and use cases.