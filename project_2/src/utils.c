/**
 * @file utils.c
 */

#include "utils.h"

int intFind(int *array, int size, int num)
{
    int i;

    if (array)
    {
        for (i = 0; i < size; i++)
        {
            if (array[i] == num) return i;
        }
    }
    return -1;
}