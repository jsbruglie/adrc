/**
 * @file queue.h
 */

#ifndef QUEUE_H
#define QUEUE_H

// Memory allocation
#include <stdlib.h>
// IO
#include <stdio.h>
// Error handling
#include <assert.h>

#include "utils.h"

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

#endif