
CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m7 -mthumb -O2 -ffreestanding -nostdlib -I./drivers
LDFLAGS=-T core/linker.ld

SRC=core/startup.s core/main.c drivers/eth.c drivers/phy.c

all:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o eth_driver.elf
	arm-none-eabi-objcopy -O binary eth_driver.elf eth_driver

sim:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o eth_driver.elf -D SIMULATION
	arm-none-eabi-objcopy -O binary eth_driver.elf eth_driver_sim

run_sim:
	qemu-system-arm -M stm32vldiscovery -kernel eth_driver.elf -nographic

clean:
	rm -f *.elf *.bin eth_driver eth_driver_sim
