build:
	gcc -Wall -o sysstatus sysstatus.c \
			statuses/tools.c \
			statuses/uptime.c \
			statuses/memusage.c \
			statuses/cpuusage.c \
			statuses/netif.c \
			statuses/netif_named.c \
			statuses/power.c \
			statuses/volume_alsa.c \
			statuses/temp.c \
			statuses/datetime.c \
			-lasound

clean:
	rm -f sysstatus
