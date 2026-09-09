/**
 * @file data.h
 * @brief Integer to ASCII and ASCII to integer conversion interface
 *
 * @author Christopher Pham
 * @date August 4, 2026
 *
 */
#ifndef __DATA_H__
#define __DATA_H__
#include <stdint.h>
#define BASE_2   (2)
#define BASE_8   (8)
#define BASE_10  (10)
#define BASE_16  (16)

#include <stdint.h>

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);
int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);

#endif /* __DATA_H__ */