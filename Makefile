CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
CFLAGS=-T linker.ld -mcpu=cortex-a7 -fpic -ffreestanding -O2 -nostdlib

os.bin: os.elf
	$(OBJCOPY) -O binary os.elf os.bin
os.elf: boot.o main.o uart.o ports.o mmu.o system.o display.o
	$(CC) $(CFLAGS) -o os.elf boot.o main.o uart.o ports.o mmu.o system.o display.o

boot.o: boot.s
	$(CC) $(CFLAGS) -c boot.s
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
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

clean:
	rm -f *.o os.*

install: os.bin
	sunxi-fel spl ../u-boot/spl/sunxi-spl.bin write 0x4a000000 os.bin exe 0x4a000000
