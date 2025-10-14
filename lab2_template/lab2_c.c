// Lab 2, uP2 Fall 2025 SOLUTIONS
// Created: 2023-07-31
// Updated: 2025-06-06
// Lab 2 is intended to be a basic introduction to a widely used communication protocol
// known as I2C. This protocol is useful in it's ability to have a large swath of
// peripherals connected to it at a time such as sensors.

/************************************Includes***************************************/

#include <stdint.h>
#include <stdbool.h>
#include <driverlib/sysctl.h>
#include <driverlib/interrupt.h>
#include <driverlib/gpio.h>
#include <driverlib/timer.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>


#include "./MultimodDrivers/multimod.h"

/************************************Includes***************************************/

/*************************************Defines***************************************/
/*************************************Defines***************************************/

/********************************Public Variables***********************************/
/********************************Public Variables***********************************/

/************************************MAIN*******************************************/

int main(void) {
    //Sets clock speed to 80 MHz. You'll need it!
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    IntMasterDisable();
    SysCtlDelay(10);

    // instantiate peripherals (UART, I2C, GPIO, etc.)
    // multimod_init();
    SPI_Init(SPI_A_BASE);

   while(1)
   {       
        SPI_WriteSingle(SPI_A_BASE, 0xAB);
        SPI_WriteSingle(SPI_A_BASE, 0xBB);
   }
}

/************************************MAIN*******************************************/
