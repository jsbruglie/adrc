/**
 * @file queue.h
 * @brief Priority queue headers
 * 
 * Implements a priority queue that has:
 * - O(1) removal of highest priority node
 * - O(d) decrease key, d number of possible values for priority or cost.
 *  This constrains the cost to a discrete set of values from 0 to values - 1.
 * 
 * @author Nuno Venturinha
 * @author João Borrego
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
    /** Size of the queue */
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

/**
 * @brief      Creates a priority queue.
 *
 * @param[in]  values  The number of possible cost values
 * @param[in]  size    The size of the queue
 *
 * @return     The priority queue
 */
PrioQueue *createPrioQueue(int values, int size);

/**
 * @brief      Deletes a priority queue
 *
 * @param      queue_ptr  The queue pointer
 */
void deletePrioQueue(PrioQueue **queue_ptr);

/**
 * @brief      Initializes an existing priority queue
 *
 * @param      queue  The queue
 */
void initPrioQueue(PrioQueue *queue);

/**
 * @brief      Prints the contents of the priority queue
 *
 * @param      queue  The queue
 */
void printPrioQueue(PrioQueue *queue);

/**
 * @brief      Extracts the node with maximum priority.
 *
 * @param      queue  The queue
 *
 * @return     The node with maximum priority.
 */
QueueNode *getMaxPriority(PrioQueue *queue);

/**
 * @brief      Lowers the cost for a given node in the queue
 *
 * If a the provided cost is higher than the current, it is disregarded
 * and the function simply returns.
 *
 * @param      queue  The queue
 * @param[in]  node   The node
 * @param[in]  cost   The new cost
 */
void decreaseKey(PrioQueue *queue, int node, int cost);

#endif