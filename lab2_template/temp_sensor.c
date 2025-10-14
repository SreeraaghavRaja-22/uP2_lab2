

/* #include "stdint.h"

#define RESET_ADDR (0xE0)
#define RESET_VALUE (0xB6)

#define MODE_ADDR (0xF4)
#define MODE_DATA_T (0b001 << 5)
#define MODE_DATA_P (0b000 << 2)
#define MODE_DATA_M (0b11 << 0)


void BME280_Init(){
    // Initialize temperature module 
    // 1. Write address 
    I2C_INIT(I2C1_BASE);

    // reset chip 
    BME280_WriteRegister(RESET_ADDR, RESET_VALUE);
    BME280_WriteRegister(MODE_ADDR, MODE_DATA_T | MODE_DATA_P | MODE_DATA_M);


}

void BME280_WriteRegister(uint8_t addr, uint8_t data)
{
    // slave addr, data 
    uint8_t temp[2] = {addr, data};
    I2C_WriteMultiple(I2C1_BASE, 0x77, temp, 2);
    uint8_t temp[3]
    I2CReadMultiple(I2C1_BASE, 0x77, temp, )

}

*/