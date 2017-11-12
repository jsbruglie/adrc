#include "queue.h"

int main(int argc, char *argv[])
{
    PrioQueue *q;
    QueueNode *n;

    q = createPrioQueue(4, 10);

    printPrioQueue(q);
    decreaseKey(q, 9, 2);
    printPrioQueue(q);
    decreaseKey(q, 3, 2);
    printPrioQueue(q);
    decreaseKey(q, 4, 1);
    printPrioQueue(q);

    n = getMaxPriority(q);
    printf("Extracted minimum cost (%d,%d)\n", n->cost, n->v);
    n = getMaxPriority(q);
    printf("Extracted minimum cost (%d,%d)\n", n->cost, n->v);

    decreaseKey(q, 8, 2);
    n = getMaxPriority(q);
    printf("Extracted minimum cost (%d,%d)\n", n->cost, n->v);

    printPrioQueue(q);

    deletePrioQueue(&q);
}