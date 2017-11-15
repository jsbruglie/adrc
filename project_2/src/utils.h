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

#define SWAP_PTR(array, idx_a, idx_b)       \
{                                           \
    void* temp = (void*) array[idx_a];      \
    array[idx_a] = (void*) array [idx_b];   \
    array[idx_b] = temp;                    \
}

#define SWAP_INT(array, idx_a, idx_b)       \
{                                           \
    int temp = array[idx_a];                \
    array[idx_a] = array[idx_b];            \
    array[idx_b] = temp;                    \
}

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

/**
 * @brief      Returns the maximum of two integers
 *
 * @param[in]  a     Integer a
 * @param[in]  b     Integer b
 *
 * @return     The max value
 */
int intMax(int a, int b);

#endif