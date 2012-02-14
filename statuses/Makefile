STATUSES=battery.o cpuusage.o datetime.o memusage.o netif.o temp.o uptime.o volume_alsa.o
OTHERS=tools.o

all: *.c *.h ../config.h Makefile $(STATUSES) $(OTHERS)

.c.o:
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f *.o
