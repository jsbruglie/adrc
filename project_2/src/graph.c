/**
 * @file graph.c
 */

#include "graph.h"

/** Resulting path type for ingoing and outgoing edge types */
type TYPE_MATRIX[CONNECTION_TYPES][CONNECTION_TYPES] =
{
    { P, R, C, I},
    { P, I, I, I},
    { P, I, I, I},
    { I, I, I, I},
};

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
            // Connection type is 0-indexed (C = 0)
            addEdge(graph, source, destination, type - 1);
        }
    }
    else
    {
        // TODO - handle incorrect file
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


type selectionOp(type in, type out)
{
    return TYPE_MATRIX[in][out];
}

void dijkstra(Graph *graph, int node, PrioQueue *queue, type* route_types)
{
    int i;
    QueueNode *min;
    AdjListNode *neighbour;
    type updated_cost;

    // Initialise route type array to I (no path)
    for (i = 0; i < graph->V; i++)
        route_types[i] = I;
    
    decreaseKey(queue, node, (int) C);

    // Main Dijkstra's algorithm loop
    for (i = 0; i < graph->V - 1; i++)
    {
        min = getMaxPriority(queue);
        //assert(min);
        route_types[min->v] = min->cost;

        // Early exit if extracted unreachable node
        if (min->cost == I) break;
        // TODO - Early exit if extracted P cost node and network is strongly connected

        // Explore extracted node neighbourhood
        neighbour = graph->lists[min->v];
        while (neighbour)
        {
            // TODO - maybe remove selectionOp function and replace with direct matrix access?
            updated_cost = selectionOp((type) min->cost, (type) neighbour->type);
            decreaseKey(queue, neighbour->destination, updated_cost);
            neighbour = neighbour->next;
        }
    }
}

void shortestPathTo(Graph *graph, int node, type* route_types)
{
    PrioQueue *queue;

    if (graph && route_types)
    {   
        // Early exit if node is completely disconnected
        if (!graph->lists[node]) return;

        // Create priority queue
        queue = createPrioQueue(CONNECTION_TYPES, graph->V);

        dijkstra(graph, node, queue, route_types);   

        // Free up resources
        deletePrioQueue(&queue);
    }
}


void printStatistics(Graph *graph, bool verbose)
{
    int i;
    PrioQueue *queue;
    type *routes;

    int total_C = 0, total_R = 0, total_P = 0, total = 0;

    if (graph)
    {
        queue = createPrioQueue(CONNECTION_TYPES, graph->V);
        routes = (type*) malloc(sizeof(type) * graph->V);
        assert(routes);

        for (i = 0; i < graph->V; i++)
        {
            // Only check nodes that are not completely disconnected
            if (graph->lists[i])
            {
                dijkstra(graph, i, queue, routes);
                // TODO - process output and get statistics
                initPrioQueue(queue);
            }
            if (verbose) printf("Working: %.2f%%\r", (i * 100.0) / (1.0 * graph->V));
        }

        deletePrioQueue(&queue);
        free(routes);
    }
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