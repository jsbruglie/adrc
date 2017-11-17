/**
 * @file graph.h
 * @brief Graph headers
 * 
 * Graph representation for networks using adjacency lists and set of tools such as:
 * - Customer cycle detection
 * - Check if network is commercially connected
 * - Determination of elected routes between nodes
 * 
 * @author Nuno Venturinha
 * @author João Borrego
 */

#ifndef GRAPH_H
#define GRAPH_H

// Memory allocation
#include <stdlib.h>
// IO
#include <stdio.h>
// Memset
#include <string.h>
// Error handling
#include <assert.h>
// Multithread
#include <omp.h>

#include "utils.h"
#include "queue.h"

/** Number of connection types */
#define EDGE_TYPES 3
/** Number of reoute types */
#define ROUTE_TYPES 4

/** Edge type code */
typedef enum { 
    /** Origin is a provider of destination */
    C_edge = 0,
    /** Origin is a peer of destination */
    R_edge,
    /** Origin is a customer of destination */
    P_edge
} EdgeType;

/** Route type code */
typedef enum{
    /** Origin uses customer route to destination */
    C = 0,
    /** Origin uses peer route to destination */
    R,
    /** Origin uses provider route to destination */
    P,
    /** Origin can not reach destination */
    I
} RouteType;

/** Node color code */
typedef enum { white=0, grey, black } color;

/**
 * @brief      Node of adjacency list
 */
typedef struct AdjListNodeStruct
{
    /** Desination of connection */
    int destination;
    /** Type of edge */
    int type;
    /** Next adjacency list node */
    struct AdjListNodeStruct* next;

} AdjListNode;

/**
 * @brief      Graph with adjacency list representation for edges
 */
typedef struct GraphStruct
{
    /** Number of vertices */
    int V;
    /** Number of edges */
    int E;
    /** Array of adjacency lists */
    AdjListNode** lists;

} Graph;

/**
 * @brief      Creates an adjacency list node.
 *
 * @param      destination  The destination node
 * @param      type         The edge type
 *
 * @return     The adjacency list node
 */
AdjListNode *createNode(int destination, int type);

/**
 * @brief      Creates a graph.
 *
 * @param      v     The number of nodes in the graph
 *
 * @return     The graph
 */
Graph *createGraph(int v);

/**
 * @brief      Adds an edge.
 *
 * @param      graph        The graph
 * @param      source       The source node
 * @param      destination  The destination node
 * @param      type         The type of edge
 */
void addEdge(Graph *graph, int source, int destination, int type);

/**
 * @brief      Creates a graph from file.
 *
 * @param      graph_file  The graph file
 *
 * @return     The graph
 */
Graph *createGraphFromFile(char *graph_file);

/**
 * @brief      Deletes the graph
 *
 * @param      graph  The graph
 */
void deleteGraph(Graph **graph);

/**
 * @brief      Aux DFS to detect cycles.
 *
 * @param      graph    The graph
 * @param      source   The source
 * @param      v_color  The array of vertex colors
 *
 * @return     True if has cycle, False otherwise.
 */
bool hasCycleDFS(Graph *graph, int source, color *v_color);

/**
 * @brief      Determines if a graph has any cycles.
 *
 * @param      graph  The graph
 *
 * @return     True if has any cycles, False otherwise.
 */
bool hasCycle(Graph *graph);

/**
 * @brief      Determines if a given node has a provider.
 *
 * @param      graph  The graph
 * @param      node   The node
 *
 * @return     True if it has provider, False otherwise.
 */
bool hasProvider(Graph *graph, int node);

/**
 * @brief      Determines if a graph is strongly connected.
 *
 * In this particular domain, we say that the graph is commercially connected
 * if a given node can reach any other in the graph. In this sense the concepts of
 * strongly and commercially connected are interchangeable.
 *
 * @param      graph  The graph
 *
 * @return     True if graph is strongly connected, False otherwise.
 */
bool isStronglyConnected(Graph *graph);

/**
 * @brief      Returns the resulting route type
 *
 * @param      edge_type   The type of edge to destination
 * @param      route_type  The type of the route so far
 *
 * @return     The resulting route type
 */
RouteType extensionOp(EdgeType edge_type, RouteType route_type);

/**
 * @brief      Dijkstra implementation
 * 
 * Calculates the type of elected route for all nodes in a graph to reach a given destination node
 *
 * @param      graph      The graph
 * @param      node       The destination node
 * @param      queue      The priority queue
 * @param      routes     The elected routes output
 * @param      connected  Whether the graph is commercially connected
 */
void dijkstra(Graph *graph, int node, PrioQueue *queue, RouteType* routes, bool connected);

/**
 * @brief      Calculates the type of elected route for all nodes to reach a destination node 
 *
 * @param      graph      The graph
 * @param      node       The destination node
 * @param      routes     The elected routes output
 * @param      connected  Whether the graph is commercially connected
 */
void shortestPathTo(Graph *graph, int node, RouteType* routes, bool connected);

/**
 * @brief      Obtains and prints elected route statistics
 * 
 * Performs a Dijkstra's algorithm call per each node in the graph in order to obtain
 * the elected routes from each node to every other in the network.
 *
 * @param      graph      The graph
 * @param      connected  Whether the graph is commercially connected
 * @param      verbose    Whether to show the progress in the terminal
 */
void printStatistics(Graph *graph, bool connected, bool verbose);

/**
 * @brief      Prints the contents of the graph adjacency list representation
 *
 * @param      graph  The graph
 */
void printGraph(Graph *graph);

#endif