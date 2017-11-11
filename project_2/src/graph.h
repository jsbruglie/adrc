/**
 * @file graph.h
 */

#ifndef GRAPH_H
#define GRAPH_H

// Memory allocation
#include <stdlib.h>
// IO
#include <stdio.h>

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


AdjListNode *createNode(int destination, int type);

Graph *createGraph(int v);

void addEdge(Graph *graph, int source, int destination, int type);

Graph *createGraphFromFile(char *graph_file);

void deleteGraph(Graph **graph);

void printGraph(Graph *graph);

#endif