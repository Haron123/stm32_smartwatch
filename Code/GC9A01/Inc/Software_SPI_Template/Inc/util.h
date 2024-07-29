#ifndef UTIL_H
#define UTIL_H

#include "stdint.h"

/**
 * @brief swaps the values of 2 addresses of Bytes
 * @param first_int a Byte, that will be swapped with the second byte
 * @param second_int a Byte, that will be swapped with the first byte
*/
void swap_byte(uint8_t* first_int, uint8_t* second_int);

#endif