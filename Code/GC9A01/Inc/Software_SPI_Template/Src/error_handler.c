#include "error_handler.h"

void error_handler(char* msg, uint32_t msg_len, char* file, uint32_t line)
{
    // Turn on Error LED
    __disable_irq();
    gpio_setup_basic(ERROR_LED_PORT, ERROR_LED_PIN, OUTPUT);
    GPIOC->BSRR = (1 << (ERROR_LED_PIN * 2));

    while(1);
}

void warning_handler(char* msg, uint32_t msg_len, char* file, uint32_t line)
{
    // Turn on Error LED
    gpio_setup_basic(ERROR_LED_PORT, ERROR_LED_PIN, OUTPUT);
    GPIOC->BSRR = (1 << (ERROR_LED_PIN * 2));
}