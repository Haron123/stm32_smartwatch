#ifndef SOFT_SPI_H
#define SOFT_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "gpio_helper.h"
#include "timer.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Soft_SPI
{
    // The gpio port as defined in the stm hal
    GPIO_TypeDef* port;

    // Master out slave in pin
    uint8_t mosi;

    // Master in Slave out pin
    uint8_t miso;

    // Chip Select pin
    uint8_t cs;

    // Serial clock pin
    uint8_t sck;

    // The clock cycle time of the scl pin 
    // in microseconds
    uint32_t clock_cycle_us;

    // The amount of microseconds
    // the dataline gets hold after setting it up
    uint32_t data_hold_us;

    // The Spi Mode the line is in
    uint8_t mode;
} Soft_SPI;

/**
 * @brief Creates a Soft_SPI struct with the given parameters and returns it
 * @param port the gpio port as GPIO_TypeDef from the stm32 HAL
 * @param mosi master out slave in
 * @param miso master in slave out
 * @param cs chip select
 * @param sck serial clock
 * @param clock_cycle_us the amount of micrseconds a clock cycle takes
 * @param data_hold_us the amount of microseconds the dataline gets hold after a change
 * also determines the amount of time the cs line is held high/low minimum
 * @param mode the spi mode it should have in the beginning
*/
Soft_SPI spi_create(GPIO_TypeDef* port, uint8_t mosi, uint8_t miso, uint8_t cs, uint8_t sck,
uint32_t clock_cycle_us, uint32_t data_hold_us, uint8_t mode);

/**
 * @brief Initializes the Pins mentioned above and I2C1
 * Side effects include: GPIO Port B clock turns on
 * 
 * @param spi_struct the spi struct that should do the task
*/
void spi_init(Soft_SPI* spi_struct);

/**
 * @brief sends the start bit for the i2c Communication
 * 
 * @param spi_struct the spi struct that should do the task
*/
void spi_start(Soft_SPI* spi_struct);

/**
 * @brief sends the stop bit for the i2c Communication
 * 
 * @param spi_struct the spi struct that should do the task
*/
void spi_stop(Soft_SPI* spi_struct);

/**
 * @brief Writes a bit to the Line
 * Waits for Transaction to be finished
 * 
 * @param spi_struct the spi struct that should do the task
 * @param data the Byte thats to send
*/
uint8_t spi_write(Soft_SPI* spi_struct, uint8_t data);

/**
 * @brief changes the SPI Mode the Master(this device)
 * transmits and receives data
 * 
 * @param spi_struct the spi struct that should do the task
 * @param mode the mode in which you want the transmission to continue in
*/
void spi_change_mode(Soft_SPI* spi_struct, uint8_t new_mode);

#ifdef __cplusplus
}
#endif

#endif
