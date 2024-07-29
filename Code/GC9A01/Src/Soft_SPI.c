#include "Soft_SPI.h"

#define PINS_PER_PORT 16

// Offset to get from the lower byte of the bsrr 
// to the higher byte
#define BSRR_L_TO_H_OFFSET 0x10 // 16

// Sets the mosi line low and waits for the data hold time
static inline void mosi_low(Soft_SPI* spi_struct)
{
  spi_struct->port->BSRR = (1 << (spi_struct->mosi + BSRR_L_TO_H_OFFSET));
  //timer_delay_us(spi_struct->data_hold_us);
}

// Sets the mosi line high and waits for the data hold time
static inline void mosi_high(Soft_SPI* spi_struct)
{
  spi_struct->port->BSRR = (1 << spi_struct->mosi);
  //timer_delay_us(spi_struct->data_hold_us);
}

// Sets the sck line low and waits for half a clock cycle
static inline void sck_low(Soft_SPI* spi_struct)
{
  spi_struct->port->BSRR = (1 << (spi_struct->sck + BSRR_L_TO_H_OFFSET));
}

// Sets the sck line high and waits for half a clock cycle
static inline void sck_high(Soft_SPI* spi_struct)
{
  spi_struct->port->BSRR = (1 << spi_struct->sck);
}

// Sets the chip select line low
static inline void cs_low(Soft_SPI* spi_struct)
{
  spi_struct->port->BSRR = (1 << (spi_struct->cs + BSRR_L_TO_H_OFFSET));
  //timer_delay_us(spi_struct->data_hold_us);
}

// Sets the chip select line high
static inline void cs_high(Soft_SPI* spi_struct)
{
  spi_struct->port->BSRR = (1 << spi_struct->cs);
  //timer_delay_us(spi_struct->data_hold_us);
}

// checks the state of the miso pin
// returns >0 if its high, returns 0 if its low
static uint8_t miso_state(Soft_SPI* spi_struct)
{
  uint8_t data = 0;

  // Fetch the lines state
  data = spi_struct->port->IDR & (1 << spi_struct->miso);

  return data;
}

Soft_SPI spi_create(GPIO_TypeDef* port, uint8_t mosi, uint8_t miso, uint8_t cs, uint8_t sck,
uint32_t clock_cycle_us, uint32_t data_hold_us, uint8_t mode)
{
  if(port == NULL)
  {
    ERROR_HANDLER("trying to access null pointer");
  }
  if(mosi >= PINS_PER_PORT || miso >= PINS_PER_PORT || cs >= PINS_PER_PORT || sck >= PINS_PER_PORT)
  {
    WARNING_HANDLER("Atleast one of the Soft_Spi pins are defined wrong");
  }

  Soft_SPI temp;
  temp.port = port;
  temp.mosi = mosi;
  temp.miso = miso;
  temp.cs = cs;
  temp.sck = sck;
  temp.clock_cycle_us = clock_cycle_us / 2;
  temp.data_hold_us = data_hold_us;
  temp.mode = mode;

  return temp;
}

void spi_init(Soft_SPI* spi_struct)
{
  // Setup Outputs
  gpio_setup_full(spi_struct->port, spi_struct->mosi, // Mosi
  OUTPUT, NO_PULL, PUSH_PULL, LOW_SPEED);
  
  gpio_setup_full(spi_struct->port, spi_struct->cs, // Chip select
  OUTPUT, NO_PULL, PUSH_PULL, LOW_SPEED);

  gpio_setup_full(spi_struct->port, spi_struct->sck,  // Serial Clock
  OUTPUT, NO_PULL, PUSH_PULL, LOW_SPEED);

  // Setup Inputs

  gpio_setup_full(spi_struct->port, spi_struct->miso, // Setup Miso
  INPUT, NO_PULL, PUSH_PULL, LOW_SPEED);

  // Setup the Idle State
  mosi_low(spi_struct);
  cs_high(spi_struct);

  // The clock idle state is different in different modes
  if(spi_struct->mode == 0 || spi_struct->mode == 1)
  {
    sck_low(spi_struct);
  }
  else if(spi_struct->mode == 2 || spi_struct->mode == 3)
  {
    sck_high(spi_struct);
  }
  
}

void spi_start(Soft_SPI* spi_struct)
{
  // Start condition
  cs_low(spi_struct);
}

void spi_stop(Soft_SPI* spi_struct)
{
  // Stop condition
  cs_high(spi_struct);
}

uint8_t spi_write(Soft_SPI* spi_struct, uint8_t data)
{
  uint8_t received_byte = 0;

  // transmit 8 bits, MSB first
  for(uint8_t i = 8; i; i--) 
  {
    if(data & 0x80)
    {
      mosi_high(spi_struct);
    }
    else
    {
      mosi_low(spi_struct);
    }
    // Shift the data 
    data<<=1;

    sck_high(spi_struct);
    sck_low(spi_struct);

    // Receive the LSB first
    received_byte |= miso_state(spi_struct);
    received_byte <<= 1;
  }

  return received_byte;
}

/*
uint8_t spi_write(Soft_SPI* spi_struct, uint8_t data)
{
  uint8_t received_byte = 0;

  // transmit 8 bits, MSB first
  for(uint8_t i = 8; i; i--) 
  {
    if(data & 0x80)
    {
      mosi_high(spi_struct);
    }
    else
    {
      mosi_low(spi_struct);
    }
    // Shift the data 
    data<<=1;

    // send a single clock pulse
    if(spi_struct->mode == 1 || spi_struct->mode == 3)
    {
      sck_low(spi_struct);
      sck_high(spi_struct);
    }
    else if(spi_struct->mode == 0 || spi_struct->mode == 2)
    {
      sck_high(spi_struct);
      sck_low(spi_struct);
    }

    // Receive the LSB first
    received_byte |= miso_state(spi_struct);
    received_byte <<= 1;
  }

  return received_byte;
}
*/