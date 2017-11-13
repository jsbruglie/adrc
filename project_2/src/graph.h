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
#define CONNECTION_TYPES 4

/** Edge type code */
typedef enum { C=0,R,P,I } type;

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


type selectionOp(type in, type out);

void dijkstra(Graph *graph, int node, PrioQueue *queue, type* route_types);

void shortestPathTo(Graph *graph, int node, type* route_types);


void printStatistics(Graph *graph, bool verbose);

/**
 * @brief      Prints the contents of the graph adjacency list representation
 *
 * @param      graph  The graph
 */
void printGraph(Graph *graph);

#endif