#include "i2c_template.h"

// Offset to get from the lower byte of the bsrr 
// to the higher byte
#define BSRR_L_TO_H_OFFSET 0x10 // 16

static void sda_high(Soft_I2C* i2c_struct)
{
  i2c_struct->port->BSRR = (1 << (i2c_struct->sda_pinnumber + BSRR_L_TO_H_OFFSET));
}

static void sda_low(Soft_I2C* i2c_struct)
{
  i2c_struct->port->BSRR = (1 << i2c_struct->sda_pinnumber);
}

static void scl_high(Soft_I2C* i2c_struct)
{
  i2c_struct->port->BSRR = (1 << (i2c_struct->scl_pinnumber + BSRR_L_TO_H_OFFSET));
}

static void scl_low(Soft_I2C* i2c_struct)
{
  i2c_struct->port->BSRR = (1 << i2c_struct->scl_pinnumber);
}

static void sda_input_mode()
{
  
}

static void sda_output_mode()
{
  
}

static uint8_t check_ack(Soft_I2C* i2c_struct)
{
  uint8_t ack_result = 0;

  scl_high();
  ack_result = sda_state();
  scl_low();
}


Soft_I2C i2c_create(GPIO_TypeDef* port, uint8_t sda_pinnumber, uint8_t scl_pinnumber,
uint32_t clock_cycle_us)
{
  if(port == NULL)
  {
    ERROR_HANDLER("trying to access null pointer");
  }
  if(sda_pinnumber > 16 || scl_pinnumber > 16)
  {
    WARNING_HANDLER("are you sure the scl and sda pins are correct?");
  }

  Soft_I2C temp;
  temp.port = port;
  temp.sda_pinnumber = sda_pinnumber;
  temp.scl_pinnumber = scl_pinnumber;
  temp.clock_cycle_us = clock_cycle_us;

  return temp;
}

void i2c_init(Soft_I2C* i2c_struct, uint8_t pullup_flag)
{
  // Setup SDA
  gpio_setup_full(i2c_struct->port, i2c_struct->sda_pinnumber,
  OUTPUT, pullup_flag, OPEN_DRAIN, LOW_SPEED);

  // Setup SCL
  gpio_setup_full(i2c_struct->port, i2c_struct->sda_pinnumber,
  OUTPUT, pullup_flag, OPEN_DRAIN, LOW_SPEED);

  scl_high(i2c_struct);
  sda_high(i2c_struct);
}

void i2c_start(Soft_I2C* i2c_struct)
{
  // Start condition
  scl_high(i2c_struct);
  timer_delay_us(timer_us_to_ticks(i2c_struct->clock_cycle_us));
  sda_low(i2c_struct);
  scl_low(i2c_struct);
  timer_delay_us(timer_us_to_ticks(i2c_struct->clock_cycle_us));
}

void i2c_stop(Soft_I2C* i2c_struct)
{
  // Stop condition
  sda_low(i2c_struct);
  scl_high(i2c_struct);
  timer_delay_us(timer_us_to_ticks(i2c_struct->clock_cycle_us));
  sda_high(i2c_struct);
}

uint8_t i2c_write(Soft_I2C* i2c_struct, uint8_t data)
{
  // transmit 8 bits, MSB first
  for(uint8_t i = 8; i; i--) 
  {
    if(data & 0x80)
    {
      sda_high(i2c_struct);
    }
    else
    {
      sda_low(i2c_struct);
    }

    data<<=1;
    scl_high(i2c_struct);
    timer_delay_us(timer_us_to_ticks(i2c_struct->clock_cycle_us));
    scl_low(i2c_struct);
    timer_delay_us(timer_us_to_ticks(i2c_struct->clock_cycle_us));
  }

  // Return the acknowledge bit
  return check_ack(i2c_struct);
}

void i2c_write_address(Soft_I2C* i2c_struct, uint8_t address, uint8_t operation)
{
  // Bit shift since the address is only the 7 last bits
  address <<= 1;

  // Add the read/write bit at the LSB 
  address |= operation;

  // transmit 8 bits, MSB first
  for(uint8_t i = 8; i > 0; i--) 
  {
    if(address & 0x80)
    {
      sda_high(i2c_struct);
    }
    else
    {
      sda_low(i2c_struct);
    }

    data<<=1;
    scl_high(i2c_struct);
    timer_delay_us(timer_us_to_ticks(i2c_struct->clock_cycle_us));
    scl_low(i2c_struct);
    timer_delay_us(timer_us_to_ticks(i2c_struct->clock_cycle_us));
  }

  // Return the acknowledge bit
  return check_ack(i2c_struct);
}