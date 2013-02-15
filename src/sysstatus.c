#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "status/battery.h"
#include "status/cpuusage.h"
#include "status/datetime.h"
#include "status/fan.h"
#include "status/memusage.h"
#include "status/netif.h"
#include "status/volume_alsa.h"
#include "status/temp.h"
#include "status/uptime.h"


void updatestatus()
{
  //status_uptime();

  status_cpuusage();

  status_battery("BAT0");
  status_battery("BAT1");

  status_memusage();

  status_netif("eth0");
  //status_netif("eth1");
  //status_netif("eth2");
  status_netif("wlan0");
  //status_netif("wlan1");
  status_netif("wlan2");
  //status_netif("usb0");
  status_netif("ppp0");

  //status_temp("GPU: ", "/sys/class/hwmon/hwmon0/device/temp4_input");
  //status_temp("CPU: ", "/sys/class/hwmon/hwmon0/device/temp2_input");
  status_temp("CPU: ", "/sys/devices/platform/coretemp.0/temp1_input");

  status_fan("Fan: ", "/sys/devices/platform/thinkpad_hwmon/fan1_input");

  status_volume_alsa("default", "Master", 0);

  status_datetime();

  fputs("\n", stdout);
  fflush(stdout);
}

int main()
{
  struct timeval tv;

  for(;;)
  {
    updatestatus();

    tv.tv_sec = UPDATE_SECS;
    tv.tv_usec = 0;

    select(0, NULL, NULL, NULL, &tv);
  }

  return 0;
}
