/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file stats.c
 * @brief Statistical analysis on an array or unsigned char data
 *
 * This program computes the min, max, min, and median of a 40 element data set.
 * This program can also sort the data from largest to smallest, and prints the results 
 * in the terminal. All stats are rounded to the nearest integer.
 * 
 *
 * @author Christopher Pham
 * @date 7/22/2026
 *
 */



#include "platform.h"
#include "stats.h"





void print_stats(unsigned char* array, unsigned int len) {

    unsigned char max = find_max(array, len);
    unsigned char min = find_min(array, len);
    unsigned char mean = find_mean(array, len);
    unsigned char med = find_median(array, len);

    PRINTF("\nStats\n");
    PRINTF("Max: %d\n", max);
    PRINTF("Min: %d\n", min);
    PRINTF("Mean: %d\n", mean);
    PRINTF("Median: %d\n", med);

    (void)max;
    (void)min;
    (void)mean;
    (void)med;
}

void print_array(unsigned char * array, unsigned int len) {
#ifdef VERBOSE
  unsigned int i;
  for (i = 0; i < len; i++) {
    PRINTF("%d ", *(array + i));
  }
  PRINTF("\n");
#else
  (void)array;
  (void)len;
#endif
}

unsigned char find_max(unsigned char* array, unsigned int len) {
    unsigned char max;

    max = array[0];

    for (unsigned int i = 1; i < len; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

unsigned char find_min(unsigned char* array, unsigned int len) {
    unsigned char min;

    min = array[0];

    for (unsigned int i = 1; i < len; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    return min;

}
 unsigned char find_mean(unsigned char* array, unsigned int len) {
        unsigned int sum = 0;
        
        for (unsigned int i = 0; i < len; i++) {
            sum = sum + array[i];
        }
        unsigned char mean = sum / len;

        return mean;
    }

    unsigned char find_median(unsigned char* array, unsigned int len) {
        unsigned char med; 

        sort_array(array, len);

        if (len % 2 == 0) {
            med = (array[len / 2 - 1] + array[len / 2]) / 2;
        }
        else {
            med = array[len / 2];
        }
        return med;
    }

    void sort_array(unsigned char* array, unsigned int len) {
        unsigned char temp;

        for (unsigned int i = 0; i < len - 1; i++){
            for (unsigned int j = 0; j < len - 1 - i; j++) {
                if(array[j] < array[j + 1]) {
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }