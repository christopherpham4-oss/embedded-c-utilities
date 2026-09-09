/**
 * @file data.c
 * @brief Integer to ASCII and ASCII to integer conversion
 *
 * @author Christopher Pham
 * @date August 4, 2026
 *
 */
#include <stdint.h>
#include "data.h"
#include "memory.h"

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base) {
  int32_t result = 0;
  uint8_t is_negative = 0;
  uint8_t i;
  uint8_t c;

if (*ptr == '-') {
  is_negative = 1;
  ptr++;
  digits--;
}

  for (i = 0; i < digits - 1; i++) {
    c = *(ptr + i);

    if (c > '9') {
        c = c - 'A' + 10;
    } else {
        c = c - '0';
    }

    result = result * base + c;
  }
if (is_negative) {
  result = -result;
}
  return result;
}

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base) {
  uint8_t length = 0;
  uint8_t is_negative = 0;
  int64_t value;
  uint8_t digit;

    if (data == 0) {
        *(ptr + 0) = '0';
        *(ptr + 1) = '\0';
        return 2;
    }

    value = data;

    if (value < 0) {
        is_negative = 1;
        value = -value;
    }

  while (value > 0) {
    digit = value % base;
    if (digit > 9) {
      digit = digit + 'A' - 10;
    } else {
      digit = digit + '0';
    }

    *(ptr + length) = digit;
length++;


    value = value / base;
  }

  if (is_negative) {
    *(ptr + length) = '-';
    length++;
  }

  my_reverse(ptr,length);

  *(ptr + length) = '\0';
  length++;

  return length;
}
