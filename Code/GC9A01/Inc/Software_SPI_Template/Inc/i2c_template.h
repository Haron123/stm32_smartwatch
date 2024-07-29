#ifndef I2C_TEMPLATE_H
#define I2C_TEMPLATe_H

#include "stm32f4xx_hal.h"
#include "gpio_helper.h"
#include "timer.h"

#define READ_OPERATION 1
#define WRITE_OPERATION 0

#ifndef NULL
#define NULL 0
#endif

typedef struct Soft_I2C
{
    // The gpio port as defined in the stm hal
    GPIO_TypeDef* port;

    // The pin number of the sda pin
    uint8_t sda_pinnumber;

    // The pin number of the scl pin
    uint8_t scl_pinnumber;

    // The clock cycle time of the scl pin 
    // in microseconds
    uint32_t clock_cycle_us;
} Soft_I2C;

/**
 * @brief Initializes the Pins mentioned above and I2C1
 * Side effects include: GPIO Port B clock turns on
*/
void i2c_init(Soft_I2C* i2c_struct, uint8_t pullup_flag);

/**
 * @brief sends the start bit for the i2c Communication
*/
void i2c_start(Soft_I2C* i2c_struct);

/**
 * @brief sends the stop bit for the i2c Communication
*/
void i2c_stop(Soft_I2C* i2c_struct);

/**
 * @brief Writes a bit to the Line
 * Waits for Transaction to be finished
 * 
 * @param data the Byte thats to send
*/
void i2c_write(Soft_I2C* i2c_struct, uint8_t data);

/**
 * @brief Writes a bit to the Line
 * Waits for Adress to be sent and received.
 * Theres no need to modify the address, the function
 * already bit shifts it to the left internally
 * 
 * @param address the Address thats to send
 * @param operation either READ or WRITE Operation
*/
void i2c_write_address(Soft_I2C* i2c_struct, uint8_t address, uint8_t operation);

#endif