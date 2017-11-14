/**
 * @file utils.c
 * @brief Utilities implementation
 * 
 * @author Nuno Venturinha
 * @author João Borrego
 */

#include "utils.h"

int intFind(int *array, int size, int number)
{
    int i;

    if (array)
    {
        for (i = 0; i < size; i++)
        {
            if (array[i] == number) return i;
        }
    }
    return -1;
}