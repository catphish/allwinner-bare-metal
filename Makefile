CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
CFLAGS=-T linker.ld -mcpu=cortex-a7 -fpic -ffreestanding -O2 -nostdlib

os.sunxi: os.bin
	mksunxiboot os.bin os.sunxi
os.bin: os.elf
	$(OBJCOPY) -O binary os.elf os.bin
os.elf: os.o main.o uart.o
	$(CC) $(CFLAGS) -o os.elf boot.o main.o uart.o

os.o: boot.s
	$(CC) $(CFLAGS) -c boot.s
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
uart.o: uart.c
	$(CC) $(CFLAGS) -c uart.c

clean:
	rm -f *.o os.*

install: os.sunxi
	sunxi-fel write 0x20000 os.sunxi
	sunxi-fel exe 0x20000
