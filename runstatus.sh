#!/bin/sh

MAXRESX=1920

RES=$(xrandr --prop | sed "s/Screen 0:[^,]*, current \(.*\) x \(.*\),.*/\1,\2/g;te;d;:e")
RESX=${RES%%,*}
RESY=${RES##*,}
FONT="-misc-fixed-medium-r-normal--13-120-75-75-C-70-iso8859-1"
#FONT="-*-fixed-medium-r-semicondensed-*-13-*-*-*-*-*-*-*"

if [ $((RESX)) -gt $((MAXRESX)) ]
then
	RESX=$((MAXRESX))
fi

cd ~/sysstatus/
killall sysstatus
./build/sysstatus | dzen2  -ta l -fn "$FONT" -bg black -w $((RESX)) -y $((RESY+82)) -h 18 -ta r -expand left -e ""
#./sysstatus | tee /dev/shm/sysstatus-log | dzen2  -ta l -fn "$FONT" -bg black -y $((RESY+82)) -h 18 -ta r -expand left -e ""
