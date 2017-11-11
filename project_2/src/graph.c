/**
 * @file graph.cpp
 */

#include "graph.h"

AdjListNode *createNode(int destination, int type)
{
    AdjListNode *node = (AdjListNode*) malloc(sizeof(AdjListNode));
    if (!node)
    {
        // TODO
    }
    node->destination = destination;
    node->type = type;
    node->next = NULL;
    return node;
}

Graph *createGraph(int v)
{
    int i;

    Graph *graph = (Graph*) malloc(sizeof(Graph));
    if (!graph)
    {
        // TODO
    } 
    graph->V = v;
    graph->E = 0;
    graph->lists = (AdjListNode**) malloc(sizeof(AdjListNode*) * (graph->V + 1));
    for (i = 0; i <= graph->V; i++)
    {
        graph->lists[i] = NULL;
    } 
    
    return graph;
}

void addEdge(Graph *graph, int source, int destination, int type)
{
    AdjListNode *node = createNode(destination, type);
    node->next = graph->lists[source];
    graph->lists[source] = node;
}

Graph *createGraphFromFile(char *text_file)
{
    Graph *graph = NULL;
    FILE *infile = fopen(text_file, "r");

    if (infile)
    {
        int node_id = 0, highest_id = 0;
        int source, destination, type;
        
        // Get node with largest id
        while (fscanf(infile, "%d", &node_id) == 1)
        {
            if (node_id > highest_id) highest_id = node_id;
        }

        rewind(infile);

        graph = createGraph(highest_id);
        while (fscanf(infile, "%d %d %d", &source, &destination, &type) == 3)
        {
            addEdge(graph, source, destination, type);
        }
    }
    else
    {
        // TODO
    }

    fclose(infile);
    return graph;
}

void deleteGraph(Graph **graph_ptr)
{
    int i;
    AdjListNode *cur, *next;
    Graph *graph = *graph_ptr;

    if (graph)
    {
        for (i = 0; i <= graph->V; i++)
        {
            cur = graph->lists[i];
            while (cur)
            {
                next = cur->next;
                free(cur);
                cur = next;
            }
            graph->lists[i] = NULL;
        }
        free(graph->lists);
        free(graph);
    }
    *graph_ptr = NULL;
}

void printGraph(Graph *graph)
{
    int i;
    AdjListNode *cur;

    if (graph)
    {
        for (i = 0; i <= graph->V; i++)
        {
            cur = graph->lists[i];
            while (cur)
            {
                printf ("src %d\t dst %d\ttype %d\n",
                    i, cur->destination, cur->type);
                cur = cur->next;
            }
        }
    }
}