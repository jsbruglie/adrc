/**
 * @file graph.h
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

#include "utils.h"
#include "queue.h"

/** Number of connection types */
#define EDGE_TYPES 3
/** Number of connection types */
#define ROUTE_TYPES 4

/** Edge type code */
typedef enum { 
    /** Origin is a provider of destination */
    C_edge = 0,
    /** Origin is a peer of destination */
    R_edge,
    /** Origin is a customer of destination */
    P_edge
} edge_type;

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
} route_type;

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
 * @param[in]  destination  The destination node
 * @param[in]  type         The edge type
 *
 * @return     The adjacency list node
 */
AdjListNode *createNode(int destination, int type);

/**
 * @brief      Creates a graph.
 *
 * @param[in]  v     The number of nodes in the graph
 *
 * @return     The graph
 */
Graph *createGraph(int v);

/**
 * @brief      Adds an edge.
 *
 * @param      graph        The graph
 * @param[in]  source       The source node
 * @param[in]  destination  The destination node
 * @param[in]  type         The type of edge
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
 * @param[in]  source   The source
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


bool hasProvider(Graph *graph, int node);

bool isStronglyConnected(Graph *graph);


route_type selectionOp(edge_type in, route_type out);

void dijkstra(Graph *graph, int node, PrioQueue *queue, route_type* routes, bool connected);

void shortestPathTo(Graph *graph, int node, route_type* routes, bool connected);


void printStatistics(Graph *graph, bool connected, bool verbose);

/**
 * @brief      Prints the contents of the graph adjacency list representation
 *
 * @param      graph  The graph
 */
void printGraph(Graph *graph);

#endif