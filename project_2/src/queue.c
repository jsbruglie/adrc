/**
 * @file queue.c
 * @brief Priority queue implementation
 * 
 * @author Nuno Venturinha
 * @author João Borrego
 */

#include "queue.h"

PrioQueue *createPrioQueue(int values, int size)
{
    int i;
    PrioQueue *queue;
    QueueNode *node;

    queue = (PrioQueue*) malloc(sizeof(PrioQueue));
    assert(queue);
    queue->values = values;
    queue->size = size;
    queue->array = (QueueNode**) malloc(size * sizeof(QueueNode*));
    assert(queue->array);
    queue->idx_array = (int*) malloc(size * sizeof(int));
    assert(queue->idx_array);
    queue->idx_block = (int*) malloc(values * sizeof(int));
    assert(queue->idx_block);

    for (i = 0; i < size; i++)
    {
        node = (QueueNode*) malloc(sizeof(QueueNode));
        assert(node);
        node->v = i;
        // Values are 0-indexed; initialize with highest value
        node->cost = values - 1;
        queue->array[i] = node;
        queue->idx_array[i] = i;
    }
    for (i = 0; i < values; i++)
    {
        queue->idx_block[i] = 0;
    }
    queue->idx_start = 0;

    return queue;
}

void deletePrioQueue(PrioQueue **queue_ptr)
{
    int i;
    int size;
    PrioQueue *queue = *queue_ptr;
    
    if (queue)
    {
        size = queue->size;
        for (i = 0; i < size; i++)
        {
            free(queue->array[i]);
        }
        free(queue->array);
        free(queue->idx_array);
        free(queue->idx_block);
        free(queue);
        *queue_ptr = NULL;
    }
}

void initPrioQueue(PrioQueue *queue)
{
    int i;
    int size, values;

    if (queue)
    {
        size = queue->size;
        values = queue->values;
        for (i = 0; i < queue->size; i++)
        {
            queue->array[i]->v = i;
            // Values are 0-indexed; initialize with highest value
            queue->array[i]->cost = queue->values - 1;
            queue->idx_array[i] = i;
        }
        for (i = 0; i < values; i++)
        {
            queue->idx_block[i] = 0;
        }
        queue->idx_start = 0;    
    }
}

void printPrioQueue(PrioQueue *queue)
{
    int i;

    if (queue)
    {
        printf("Queue:\t");
        for (i = 0; i < queue->size; i++)
        {
            printf("(%d,%d) ", queue->array[i]->v, queue->array[i]->cost);
        }
        printf("\nIdx:\t");
        for (i = 0; i < queue->size; i++)
        {
            printf("(%d,%d) ", i, queue->idx_array[i]);
        }
        printf("\n\tStart %d Block idx ", queue->idx_start);
        for (i = 0; i < queue->values; i++)
        {
            printf("%d ", queue->idx_block[i]);
        }
        printf("\n");
    }
}

QueueNode *getMaxPriority(PrioQueue *queue)
{
    QueueNode *min;

    if (queue)
    {
        if (queue->idx_start < queue->size)
        {
            min = queue->array[queue->idx_start];
            queue->idx_start++;
            return min;
        }
    }
    return NULL;
}

void decreaseKey(PrioQueue *queue, int node, int cost)
{
    int i;
    int idx_node, block_start;
    int old_cost;

    int j;

    if (queue)
    {
        // Index of node in queue that needs to be updated
        idx_node = queue->idx_array[node];
        // Only update cost if it decreases
        old_cost = queue->array[idx_node]->cost;
        if (cost < old_cost)
        {
            // Update node cost
            queue->array[idx_node]->cost = cost;
            
            // Fix first node of each non-empty block
            for (i = cost + 1; i <= old_cost; i++)
            {
                // Swap out of place node of block i with first in block i + 1,
                //  thus fixing block i
                block_start = queue->idx_block[i];

                // Only perform swap if block is not empty
                if (queue->array[block_start]->cost == i)
                {
                    queue->idx_array[queue->array[idx_node]->v] = block_start;
                    queue->idx_array[queue->array[block_start]->v] = idx_node;
                    SWAP_PTR(queue->array, idx_node, block_start);
                }
                // Fix block start indices
                queue->idx_block[i]++;
            }
        }
    }
}