#include "util.h"

void swap_byte(uint8_t* first_int, uint8_t* second_int)
{
  uint32_t temp = *first_int;
  *first_int = *second_int;
  *second_int = temp;
}