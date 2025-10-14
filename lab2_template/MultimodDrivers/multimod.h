#ifndef MULTIMOD_H_
#define MULTIMOD_H_

#include "multimod_BMI160.h"
#include "multimod_i2c.h"
#include "multimod_OPT3001.h"
#include "multimod_uart.h"
#include "multimod_spi.h"
#include "multimod_ST7789.h"
#include "SPI_string.h"

static void multimod_init(){
    UART_Init();
    I2C_Init(I2C_A_BASE);
    BMI160_Init();
    OPT3001_Init();
    ST7789_Init();
}

#endif /* MULTIMOD_H_ */
