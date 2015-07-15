#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "config.h"
#include "statuses.h"


static char outline[4096];

static GlobalData gd = {
  .line = outline,
  .linemax = sizeof(outline),
};


void updatestatus()
{
  GlobalData *g = &gd;


  line_clear(g);

  //status_uptime(g);

  status_cpuusage(g);

  status_battery(g, "BAT0");
  status_battery(g, "BAT1");

  status_memusage(g);

  status_netif(g, "eth0");
  //status_netif(g, "eth1");
  //status_netif(g, "eth2");
  //status_netif(g, "eth3");
  status_netif(g, "eth4");
  status_netif(g, "wlan0");
  status_netif(g, "wlan1");
  status_netif(g, "wlan2");
  status_netif(g, "usb0");
  status_netif(g, "usb1");
  status_netif(g, "ppp0");
  //status_netif(g, "ppp1");

  //status_temp("GPU: ", "/sys/class/hwmon/hwmon0/device/temp4_input");
  //status_temp("CPU: ", "/sys/class/hwmon/hwmon0/device/temp2_input");
  status_temp(g, "CPU: ", "/sys/devices/platform/coretemp.0/temp1_input");

  status_fan(g, "Fan: ", "/sys/devices/platform/thinkpad_hwmon/fan1_input");

  if (status_volume_alsa(g, "default", "Master", 0))
  if (status_volume_alsa(g, "default", "PCM", 0))
  if (status_volume_alsa(g, "default", "Headset", 0))
    ;

  status_datetime(g);

  line_print(g);

  fflush(stdout);
}

int main()
{
  struct timeval tv;

  /* Initial JSON header for i3bar */
  printf("{\"version\":1}\n[\n");

  for(;;)
  {
    updatestatus();

    tv.tv_sec = UPDATE_SECS;
    tv.tv_usec = 0;

    select(0, NULL, NULL, NULL, &tv);
  }

  return 0;
}
