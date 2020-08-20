
CC=../tool/arm-none-eabi-gcc/bin/arm-none-eabi-gcc
LD=../tool/arm-none-eabi-gcc/bin/arm-none-eabi-ld
CP=../tool/arm-none-eabi-gcc/bin/arm-none-eabi-objcopy
LDSCRIPT=gboot.lds
CPPFLAGS=-MMD


.PHONY : all clean

all : gboot.bin gboot.elf

gboot.bin : gboot.elf
	$(CP) -O binary $< $@

gboot.elf : start.o main.o led.o button.o interrupt.o nandflash.o
	$(LD) -T$(LDSCRIPT) $^ -o $@

%.o : %.S
	$(CC) -c -g $<

%.o : %.c
	$(CC) $(CPPFLAGS) -c -g $<

-include $(wildcard *.d)

clean:
	-rm -rf *.o *.bin *.elf *.d
