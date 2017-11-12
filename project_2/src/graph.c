/**
 * @file graph.c
 */

#include "graph.h"

AdjListNode *createNode(int destination, int type)
{
    AdjListNode *node = (AdjListNode*) malloc(sizeof(AdjListNode));
    assert(node);
    node->destination = destination;
    node->type = type;
    node->next = NULL;
    return node;
}

Graph *createGraph(int v)
{
    int i;

    Graph *graph = (Graph*) malloc(sizeof(Graph));
    assert(graph);
    // Nodes are 0-indexed
    graph->V = v + 1;
    graph->E = 0;
    graph->lists = (AdjListNode**) malloc(sizeof(AdjListNode*) * (graph->V));
    for (i = 0; i < graph->V; i++)
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
    graph->E++;
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
        for (i = 0; i < graph->V; i++)
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

bool hasCycleDFS(Graph *graph, int source, color *v_color)
{
    AdjListNode *cur;

    v_color[source] = grey;
    cur = graph->lists[source];

    while (cur)
    {
        // Only need to consider customer provider (type C) edges
        if (cur->type == C)
        {
            if (v_color[cur->destination] == grey)
            {
                return true;
            }
            else if (v_color[cur->destination] == white)
            {
                if (hasCycleDFS(graph, cur->destination, v_color))
                    return true; 
            }
        }
        cur = cur->next;
    }
    v_color[source] = black;
    return false;
}

bool hasCycle(Graph *graph)
{
    int i;
    bool found_cycle = false;

    if (graph)
    {
        // TODO Proper malloc; V not known at compile time
        color v_color[graph->V];
        
        for (i = 0; i < graph->V; i++)
        {
            v_color[i] = white;
        }

        for (i = 0; i < graph->V; i++)
        {
            if (v_color[i] == white)
            {
                found_cycle = hasCycleDFS(graph, i, v_color);
                if (found_cycle)
                    break;
            }
        }
    }
    return found_cycle;
}

bool hasProvider(Graph *graph, int node)
{
    AdjListNode *cur;
    bool has_provider = false;

    if (graph)
    {
        cur = graph->lists[node];
        while (cur)
        {
            if (cur->type == P)
            {
                has_provider = true;
                break; 
            }
            cur = cur->next;
        }
    }
    return has_provider;
}

bool isStronglyConnected(Graph *graph)
{
    int i, j = 0;
    AdjListNode *cur;
    int n_top, idx;

    if (!graph) return false;

    int top_tier_candidates[graph->V];

    // Start by obtaining nodes that have no providers, i.e., tier-1
    for (i = 0; i < graph->V; i++)
    {
        // Ensure node exists
        if (graph->lists[i] && !hasProvider(graph, i)){
            top_tier_candidates[j++] = i;
        }
    }

    n_top = j;

    bool peer_connected[n_top];

    debugPrintLn("Found %d tier-1 nodes: ", n_top);
    debugPrint("\t");
    for (i = 0; i < n_top; i++){
        debugPrint("%d ", top_tier_candidates[i]);
    }
    debugPrint("\n");
    
    debugPrintLn("Tier-1 node peer connections");

    // Check if each of the tier-1 nodes hava a peer connection to every other node
    for (i = 0; i < n_top; i++)
    {
        memset(peer_connected, 0, n_top * sizeof(bool));

        cur = graph->lists[top_tier_candidates[i]];
        while (cur)
        {
            // TODO - Avoid double checking for certain connections
            if (cur->type == R)
            {
                idx = intFind(top_tier_candidates, n_top, cur->destination);
                peer_connected[idx] = true;
            }
            cur = cur->next;
        }

        debugPrint("\tNode %d connections:\t", top_tier_candidates[i]);
        for (j = 0; j < n_top; j++){
            debugPrint("%d ", peer_connected[j]);
        }
        debugPrint("\n");

        // Check if a tier-1 candidate is connected to the remaining candidates
        for (j = 0; j < i; j++)
        {
            if (!peer_connected[j])
            {
                return false;
            }
        }
    }

    return true;
}

void printGraph(Graph *graph)
{
    int i;
    AdjListNode *cur;

    if (graph)
    {
        printf("Graph\tV %d\tE %d\n", graph->V, graph->E);
        for (i = 0; i < graph->V; i++)
        {
            cur = graph->lists[i];
            while (cur)
            {
                printf("src %d\tdst %d\ttype %d\n",
                    i, cur->destination, cur->type);
                cur = cur->next;
            }
        }
    }
}