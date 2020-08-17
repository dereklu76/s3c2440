
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
CP=arm-none-eabi-objcopy
LDSCRIPT=gboot.lds


.PHONY : all clean

all : gboot.bin gboot.elf

gboot.bin : gboot.elf
	$(CP) -O binary $< $@

gboot.elf : start.o main.o
	$(LD) -T$(LDSCRIPT) $^ -o $@

%.o : %.S
	$(CC) -c -g $<

%.o : %.c
	$(CC) -c -g $<

clean:
	rm -rf *.o *.bin *.elf
