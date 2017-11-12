/**
 * @file utils.h
 */

#ifndef UTILS_H
#define UTILS_H

//#define VERBOSE

#ifdef VERBOSE
#define debugPrintLn(M, ...) printf("DEBUG: %s:%d:%s: " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define debugPrint(M, ...) printf(M, ##__VA_ARGS__)
#else
#define debugPrintLn(M, ...)
#define debugPrint(M, ...)
#endif

#define errPrint(M, ...) fprintf(stderr, "ERROR: %s:%d:%s: " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

/** Boolean types */
typedef enum { false=0, true } bool;

/**
 * Functions
 */

/**
 * @brief      Finds the index of the first instance of a number in an array
 *
 * @param      array  The array
 * @param[in]  size   The size of the array
 * @param[in]  number The number
 *
 * @return     Index of first instance of number in array
 */
int intFind(int *array, int size, int number);

#endif