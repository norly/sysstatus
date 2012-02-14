STATUSES=cpuusage.o datetime.o memusage.o netif.o power.o temp.o uptime.o volume_alsa.o
OTHERS=tools.o

all: *.c *.h Makefile $(STATUSES) $(OTHERS)

.c.o:
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f *.o
