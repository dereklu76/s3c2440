OBJS := button.o interrupt.o led.o nandflash.o uart.o lcd.o touchscreen.o

dev.o : $(OBJS)
	$(LD) -r $^ -o dev.o

%.o : %.c
	$(CC) $(CFLAGS) $< -c

%.o : %.S
	$(CC) $(CFLAGS) $< -c

-include $(wildcard *.d)

clean:
	-rm -f *.o *.d




