objs := div64.o lib1funcs.o ctype.o muldi3.o printf.o string.o vsprintf.o

lib.o : $(objs)
	$(LD) -r -o lib.o $^
	
%.o : %.c
	$(CC) ${CFLAGS} -c $<
	
%.o : %.S
	$(CC) ${CFLAGS} -c $<

-include $(wildcard *.d)

clean:
	-rm -f *.o *.d		
	
