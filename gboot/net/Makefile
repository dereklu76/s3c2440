OBJS := arp.o

net.o : $(OBJS)
	$(LD) -r $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

-include $(wildcard *.d)

clean :
	-rm -f *.o *.d

