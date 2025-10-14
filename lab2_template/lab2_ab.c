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
    multimod_init();

   uint8_t BMI_DeviceID = BMI160_ReadRegister(BMI160_CHIPID_ADDR); // The ID is 0xD1

   uint16_t OPT_DeviceID = (uint16_t)OPT3001_ReadRegister(OPT3001_DEVICEID_ADDR); // The ID is 0x3001

   while(1)
   {
        // get the accel x data 
        int16_t accel_data = BMI160_AccelXGetResult();

        // get the light sensor data 
        uint32_t light_data = OPT3001_GetResult();


        // convert light data from 0 to 2048
        light_data = (light_data / 80000.0f) * 2048.0f;
        
        if (light_data > 2048.0f){light_data = 2048.0f;}

        // print using UART
        UARTprintf("accel X value: %d\noptical value: %d\n\n", accel_data, light_data);
   }
}

/************************************MAIN*******************************************/
