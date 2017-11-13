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
    bool has_cycle, is_connected;

    if (argc != 2){
        printUsage();
        exit(EXIT_FAILURE);
    }

    graph = createGraphFromFile(argv[1]);

    //printGraph(graph);

    has_cycle = hasCycle(graph);
    is_connected = isStronglyConnected(graph);

    printf("Graph has cycles %d\n", has_cycle);
    printf("Graph is strongly connected %d\n", is_connected);
    
    /*
    int node = 1234;
    route_type routes[graph->V];
    shortestPathTo(graph, node, routes, false);
    int i;
    for (i = 0; i < graph->V; i++){
        if (graph->lists[i] && i != node)
        { 
            // TODO why is the route type output inverted?
            printf("%d %d %d\n", i, (routes[i] + 1), node);
        }
    }
    */
    
    //printStatistics(graph, true, connected);

    deleteGraph(&graph);
}