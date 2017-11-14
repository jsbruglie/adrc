/** 
 * @file main.c
 * @brief Main project 2 executable
 * 
 * Reads a graph file representing a network, detects whether it has customer cycles
 * and whether it is comercially connected. Finally it presents statistics regarding
 * the types of routes elected by each node in order to reach every other in the network.
 *
 * @author Nuno Venturinha
 * @author João Borrego
*/

#include "graph.h"

// DEBUG
void printElectedRoutesToNode(Graph *graph, int node, bool connected);

/**
 * @brief      Prints usage information to terminal
 *
 * @param      argv  The argv
 */
void printUsage(char *argv[])
{
    printf("%s <input.graph>\n", argv[0]);
}

/**
 * @brief      The main program
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 *
 * @return     0
 */
int main(int argc, char *argv[])
{

    Graph *graph;
    bool has_cycle, is_connected;

    if (argc != 2){
        printUsage(argv);
        exit(EXIT_FAILURE);
    }

    graph = createGraphFromFile(argv[1]);

    has_cycle = hasCycle(graph);
    is_connected = isStronglyConnected(graph);

    printf("Graph has %scustomer cycles.\n", (has_cycle)? "" : "no ");
    printf("Graph is %sstrongly connected.\n", (is_connected)? "" : "not ");

    printStatistics(graph, is_connected, true);

    //printElectedRoutesToNode(graph, 1234, is_connected);

    deleteGraph(&graph);

    return 0;
}

// DEBUG
void printElectedRoutesToNode(Graph *graph, int node, bool connected)
{
    int i;
    RouteType routes[graph->V];
    shortestPathTo(graph, node, routes, connected);
    for (i = 0; i < graph->V; i++){
        if (graph->lists[i] && i != node)
        { 
            printf("%d %d %d\n", i, (routes[i] + 1), node);
        }
    }
}