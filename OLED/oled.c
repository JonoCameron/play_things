// Runs 128x64 OLED display with I2C protocol.
// SSD1306 OLED driver.
// It's French he said. From M'aidez
// Help me.

#include "stdio.h"
#include "linux/i2c-dev.h"
#include "sys/ioctl.h"
#include "unistd.h"
#include "fcntl.h"


struct I2CRegs{
    reg32 control;              // control
    reg32 status;               // status
    reg32 data_length;          // data length
    reg32 slave_address;        // slave address
    reg32 data_fifo;            // data fifo
    reg32 clock_divider;        // clock divider
    reg32 data_delay;           // data delay
    reg32 clock_stretch_timeout // clock stretch timeout
}

// Control register
#define C_I2CEN (1 << 15)
#define C_INTR  (1 << 10)
#define C_INTT  (1 << 9)
#define C_INTD  (1 << 8)
#define C_ST    (1 << 7)
#define C_CLEAR (1 << 5)
#define C_READ  (1 << 0)

// Status register
#define S_CLKT  (1 << 9)
#define S_ERR   (1 << 8)
#define S_RXF   (1 << 7)
#define S_TXE   (1 << 6)
#define S_RXD   (1 << 5)
#define S_TXD   (1 << 4)
#define S_RXR   (1 << 3)
#define S_TXW   (1 << 2)
#define S_DONE  (1 << 1)
#define S_TA    (1 << 0)

#define REGS_I2C ((struct I2CRegs*))(BSC1)
#define BCM2711_PERI_BASE   0x7e200000
#define BSC1: 0x7e804000




int main(){
    printf("Hello OLED.\n");

    return 0;
}