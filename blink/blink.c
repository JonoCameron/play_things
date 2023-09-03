// Blinks RPi GPIO 2
// https://elinux.org/RPi_GPIO_Code_Samples#Direct_register_access
// https://datasheets.raspberrypi.com/bcm2711/bcm2711-peripherals.pdf
// https://www.youtube.com/watch?v=mshVdGlGwBs

//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//  Revised: 15-Feb-2013

#define BCM2711_PERI_BASE   0x7e200000

// Access from ARM Running Linux

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int mem_fd;
int a;
void *gpio_map;

// I/O access
volatile unsigned *gpio;

// GPIO macros. I'll let you figure them out the same way I had to. It's good for you x
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(0<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)
#define GPIO_CLR *(gpio+10)

void setup_io();
void handle_sigint(int sig);

int main(int argc, char **argv)
{
    // Set up gpio pointer for direct register access
    setup_io();
    signal(SIGINT, handle_sigint);

    OUT_GPIO(21);

    while(1){
        GPIO_SET = 1<<21;
        printf("On\n");
        for(int i = 0; i < 500000000; i++){
            // do nothing but I think the compiler will optimise this out?
            a = 0;
            a = a + 1;
        }

        GPIO_CLR = 1<<21;
        printf("Off\n");
        for(int i = 0; i < 500000000; i++){
            // do nothing but I think the compiler will optimise this out?
            a = 0;
            a = a + 1;
        }
    }
} // main


//
// Set up a memory regions to access GPIO
//
void setup_io()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/gpiomem", O_RDWR|O_SYNC) ) < 0) {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    /* mmap GPIO */
    gpio_map = mmap(
        NULL,                   //Any adddress in our space will do
        BLOCK_SIZE,             //Map length
        PROT_READ|PROT_WRITE,   //Enable reading & writing to mapped memory
        MAP_SHARED,             //Shared with other processes
        mem_fd,                 //File to map
        BCM2711_PERI_BASE       //Offset to GPIO peripheral
    );

    close(mem_fd); //No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED) {
        printf("mmap error %d\n", (long int)gpio_map);//errno also set!
        exit(-1);
    }

    // Always use volatile pointer!
    gpio = (volatile unsigned *)gpio_map;


} // setup_io

void handle_sigint(int sig) {
    printf("\nCaught signal: %d\n", sig);
    GPIO_CLR = 1<<21;
    exit(0);
} //handle_sigint