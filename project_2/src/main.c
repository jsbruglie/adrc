/** 
* @file main.cpp
* @brief Main project executable
*
* @author Nuno Venturinha
* @author João Borrego
*/

#include "graph.h"

void printUsage()
{
    return;
}

int main(int argc, char *argv[])
{

    if (argc != 2){
        printUsage();
        exit(EXIT_FAILURE);
    }

    Graph *g = createGraphFromFile(argv[1]);

    printGraph(g);
    
    bool has_cycle = hasCycle(g);
    printf("\nGraph has cycles %d\n", has_cycle);

    deleteGraph(&g);
}