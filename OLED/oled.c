// Runs 128x64 OLED display with I2C protocol.
// SSD1306 OLED driver.
// It's French he said. From M'aidez
// Help me.

#include "stdio.h"
#include "linux/i2c-dev.h"
#include "sys/ioctl.h"
#include "unistd.h"
#include "fcntl.h"

#define BCM2711_PERI_BASE   0x7e200000
//BSC1: 0x7e804000

int main(){
    printf("Hello OLED.\n");

    return 0;
}