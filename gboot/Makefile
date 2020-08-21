OBJS := start.o main.o lib/lib.o dev/dev.o
CC := $(shell pwd)/../tool/arm-none-eabi-gcc/bin/arm-none-eabi-gcc
LD := $(shell pwd)/../tool/arm-none-eabi-gcc/bin/arm-none-eabi-ld
CP := $(shell pwd)/../tool/arm-none-eabi-gcc/bin/arm-none-eabi-objcopy
LDSCRIPT := gboot.lds
CPPFLAGS := -MMD
CPPFLAGS += -I$(shell pwd)/include 
CPPFLAGS += -I$(shell pwd)/lib
CPPFLAGS += -I$(shell pwd)/dev
CFLAGS:=$(CPPFLAGS) -fno-builtin 

export CC
export LD
export CFLAGS

.PHONY : clean lib/lib.o dev/dev.o

gboot.bin : gboot.elf
	$(CP) -O binary $< $@

gboot.elf : $(OBJS) 
	$(LD) -T$(LDSCRIPT) $^ -o $@

lib/lib.o :
	make -C lib/

dev/dev.o :
	make -C dev/

%.o : %.S
	$(CC) -c -g $<

%.o : %.c
	$(CC) $(CFLAGS) -c -g $<

-include $(wildcard *.d)

clean:
	-rm -rf *.o *.bin *.elf *.d
	make -C dev clean
	make -C lib clean
