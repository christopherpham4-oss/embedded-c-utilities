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
 * @file stats.h
 * @brief Function declarations for statistical analysis on an array of data
 *
 * This heaeer declares functions used to find the min, max, mean, 
 * and median of an array of unsigned char data. It also declares functions 
 * to help sort the data from largest to smallest and to print the array and 
 * statistics.
 *
 * @author Christopher Pham
 * @date 7/22/2026
 *
 */
#ifndef __STATS_H__
#define __STATS_H__
#include "platform.h"

/* Add Your Declarations and Function Comments here */ 

/**
 * @brief Prints the statistics of the array
 *
 * Prints the max, min, mean, and median of the diven data set.
 *
 * @param array Pointer to an array of unsigned char data
 * @param len Length of the array
 *
 * @return void
 */
void print_stats(unsigned char* array, unsigned int len);

/**
 * @brief Prints an array to the terminal
 *
 * Prints every element of the given array.
 *
 * @param array Pointer to an array of unsigned char data
 * @param len Length of the array
 *
 * @return void
 */
void print_array(unsigned char* array, unsigned int len);

/**
 * @brief Finds the median of an array
 *
 * Sorts the array and returns the middle value. For an array with an even
 * number of elements, the average of the two middle values is returned. The
 * result is rounded down to the nearest integer. This function first sorts 
 * the array.
 *
 * @param array Pointer to an array of unsigned char data
 * @param len Length of the array
 *
 * @return unsigned char The median value of the data set
 */
unsigned char find_median(unsigned char* array, unsigned int len);

/**
 * @brief Finds the mean of an array
 *
 * Sums every element of the array and divides by the number of elements. The
 * result is rounded down to the nearest integer.
 *
 * @param array Pointer to an array of unsigned char data
 * @param len Length of the array
 *
 * @return unsigned char The mean value of the data set
 */
unsigned char find_mean(unsigned char* array, unsigned int len);

/**
 * @brief Finds the largest value in an array
 *
 * Steps through the array and stores the largest value found.
 *
 * @param array Pointer to an array of unsigned char data
 * @param len Length of the array
 *
 * @return unsigned char The maximum value of the data set
 */
unsigned char find_max(unsigned char* array, unsigned int len);

/**
 * @brief Finds the smallest value in an array
 *
 * Steps through the array and stores the smallest value found.
 *
 * @param array Pointer to an array of unsigned char data
 * @param len Length of the array
 *
 * @return unsigned char The minimum value of the data set
 */
unsigned char find_min(unsigned char* array, unsigned int len);

/**
 * @brief Sorts an array from largest to smallest
 *
 * Sorts the array in place so that the first(0) element holds the largest value
 * and the last element holds the smallest value.
 *
 * @param array Pointer to an array of unsigned char data
 * @param len Length of the array
 *
 * @return void
 */
void sort_array(unsigned char* array, unsigned int len);

#endif /* __STATS_H__ */