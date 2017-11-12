/**
 * @file queue.h
 */

// Memory allocation
#include <stdlib.h>
// IO
#include <stdio.h>
// Error handling
#include <assert.h>

#define SWAP_PTR(array, idx_a, idx_b)       \
{                                           \
    void* temp = (void*) array[idx_a];      \
    array[idx_a] = (void*) array [idx_b];   \
    array[idx_b] = temp;                    \
}

#define SWAP_INT(array, idx_a, idx_b)       \
{                                           \
    int temp = array[idx_a];                \
    array[idx_a] = array [idx_b];           \
    array[idx_b] = temp;                    \
}

typedef struct QueueNodeStruct
{   
    /** Graph node identifier */
    int v;
    /** Current cost for a respective node */
    int cost;

} QueueNode;

typedef struct PrioQueueStruct
{   
    /** Number of possible values for cost */
    int         values;
    /** Dimension of set of possible values for cost */
    int         size;
    /** Node array */
    QueueNode   **array;
    /** Node index array */
    int         *idx_array;
    /** Index of the start of a block which holds nodes with the same cost */
    int         *idx_block;
    /** Index of the start of the nodes yet to be removed */
    int         idx_start;

} PrioQueue;

PrioQueue *createPrioQueue(int values, int size);

void deletePrioQueue(PrioQueue **queue_ptr);

void initPrioQueue(PrioQueue *queue);

void printPrioQueue(PrioQueue *queue);

QueueNode *getMaxPriority(PrioQueue *queue);

void decreaseKey(PrioQueue *queue, int node, int cost);