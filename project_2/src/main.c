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

    Graph *graph;
    bool rv;

    if (argc != 2){
        printUsage();
        exit(EXIT_FAILURE);
    }

    graph = createGraphFromFile(argv[1]);

    //printGraph(graph);
    
    rv = hasCycle(graph);
    printf("Graph has cycles %d\n", rv);

    rv = isStronglyConnected(graph);
    printf("Graph is strongly connected %d\n", rv);

    deleteGraph(&graph);
}