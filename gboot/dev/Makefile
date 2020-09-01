OBJS := button.o interrupt.o led.o nandflash.o uart.o lcd.o touchscreen.o dm9000.o

dev.o : $(OBJS)
	$(LD) -r $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -c

-include $(wildcard *.d)

clean:
	-rm -f *.o *.d




