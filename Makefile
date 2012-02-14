CC=gcc
CCFLAGS=-Wall -Wextra -O3
LDOUT=sysstatus
LIBS=-lasound

all: *.c *.h Makefile
	make -C statuses
	$(CC) $(CCFLAGS) -o $(LDOUT) $(LIBS) sysstatus.c statuses/*.o

clean:
	make -C statuses clean
	rm -f sysstatus
