CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
CFLAGS=-T linker.ld -mcpu=cortex-a7 -fpic -ffreestanding -O2 -nostdlib

os.bin: os.elf
	$(OBJCOPY) -O binary os.elf os.bin
os.elf: boot.o startup.o uart.o ports.o mmu.o system.o display.o interrupts.o
	$(CC) $(CFLAGS) -o os.elf boot.o startup.o uart.o ports.o mmu.o system.o display.o interrupts.o

boot.o: boot.s
	$(CC) $(CFLAGS) -c boot.s
startup.o: startup.c
	$(CC) $(CFLAGS) -c startup.c
uart.o: uart.c
	$(CC) $(CFLAGS) -c uart.c
ports.o: ports.c
	$(CC) $(CFLAGS) -c ports.c
mmu.o: mmu.c
	$(CC) $(CFLAGS) -c mmu.c
system.o: system.c
	$(CC) $(CFLAGS) -c system.c
display.o: display.c
	$(CC) $(CFLAGS) -c display.c
interrupts.o: interrupts.c
	$(CC) $(CFLAGS) -c interrupts.c

clean:
	rm -f *.o os.*

install: os.bin
	sunxi-fel spl ../u-boot/spl/sunxi-spl.bin write 0x40000000 os.bin exe 0x40000000
