// Lab 2, uP2 Fall 2025 SOLUTIONS
// Created: 2023-07-31
// Updated: 2025-06-06
// Lab 2 is intended to be a basic introduction to a widely used communication protocol
// known as I2C. This protocol is useful in it's ability to have a large swath of
// peripherals connected to it at a time such as sensors.

/************************************Includes***************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <driverlib/sysctl.h>
#include <driverlib/interrupt.h>
#include <driverlib/gpio.h>
#include <driverlib/timer.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include "GFX_Library.h"


#include "./MultimodDrivers/multimod.h"

/************************************Includes***************************************/

/*************************************Defines***************************************/
/*************************************Defines***************************************/

/********************************Public Variables***********************************/
/********************************Public Variables***********************************/

/************************************MAIN*******************************************/

char* citoa(int num, char* str, int base);

int main(void) {
    //Sets clock speed to 80 MHz. You'll need it!
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    IntMasterDisable();
    SysCtlDelay(10);


    // instantiate peripherals (UART, I2C, GPIO, etc.)
    multimod_init();
    
    ST7789_Fill(ST7789_WHITE);

    // unlock SW2 before using it
    //SysCtlPeripheralEnable(GPIO_PORTF_BASE);
    //while(!(SysCtlPeripheralReady(GPIO_PORTF_BASE)));

    GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    
    // new tech I learned
   while(1){
      //set text color, color background, text size, 
      display_setTextColor(ST7789_BLACK);
      display_setTextColorBg(ST7789_BLACK, ST7789_WHITE);
      display_setTextSize(2);
      
      char accel_buf[64];
      char optical_buf[64];

      int16_t accel_data = BMI160_AccelXGetResult();

      // get the light sensor data 
      uint32_t light_data = OPT3001_GetResult();

      // normalize the data
      // convert light data from 0 to 2048
      light_data = (light_data / 80000.0f) * 2048.0f;
    
      if (light_data > 2048.0f){light_data = 2048.0f;}


      if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == GPIO_PIN_0)){
        while(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == GPIO_PIN_0));
            display_fillScreen(ST7789_WHITE);
            ST7789_DrawStringStatic("Accel X Data: ", ST7789_BLACK, 10, 250);
            ST7789_DrawStringStatic(citoa(accel_data, accel_buf, 10), ST7789_BLACK, 120, 250);
            display_drawLine(0, 200, X_MAX-1, 200, ST7789_BLACK);
            ST7789_DrawStringStatic("Optical Data: ", ST7789_BLACK, 10, 150);
            ST7789_DrawStringStatic(citoa(light_data, optical_buf, 10), ST7789_BLACK, 120, 150);
            display_drawLine(0, 100, X_MAX-1, 100, ST7789_BLACK);
            ST7789_DrawStringStatic("JR Yamanote Line", ST7789_BLACK, 10, 50);

      }
    }
}

// got following functions from this website
// https://www.geeksforgeeks.org/c/implement-itoa/
void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

// Implementation of citoa()
char* citoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled
    // only with base 10. Otherwise numbers are
    // considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}



/************************************MAIN*******************************************/
