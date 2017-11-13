/**
 * @file graph.c
 */

#include "graph.h"

/** Resulting path type for ingoing and outgoing edge types */
route_type TYPE_MATRIX[EDGE_TYPES][ROUTE_TYPES] =
{
    { P, P, P, I},
    { R, I, I, I},
    { C, I, I, I}
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
            // Connection type is 0-indexed (C_edge = 0)
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
        if (cur->type == C_edge)
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
            if (cur->type == P_edge)
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
            if (cur->type == R_edge)
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


route_type selectionOp(edge_type in, route_type out)
{
    return TYPE_MATRIX[in][out];
}

void dijkstra(Graph *graph, int node, PrioQueue *queue, route_type* routes, bool connected)
{
    int i;
    QueueNode *min;
    AdjListNode *neighbour;
    route_type initial_cost = (connected)? P : I; 
    route_type updated_cost;

    // Initialise route type array to I (no path)
    for (i = 0; i < graph->V; i++)
        routes[i] = initial_cost;
    
    decreaseKey(queue, node, (int) C);

    // Main Dijkstra's algorithm loop
    for (i = 0; i < graph->V; i++)
    {
        min = getMaxPriority(queue);
        //assert(min);
        routes[min->v] = min->cost;

        // Early exit if extracted unreachable node
        if (min->cost == I) break;
        // TODO - Early exit if extracted P cost node and network is strongly connected
        if (connected && min->cost == P) break;

        // Explore extracted node neighbourhood
        neighbour = graph->lists[min->v];
        while (neighbour)
        {   
            // If neighbour has not been extracted from priority queue
            if (routes[neighbour->destination] == initial_cost)
            {
                // TODO - maybe remove selectionOp function and replace with direct matrix access?
                updated_cost = selectionOp((edge_type) neighbour->type, (route_type) min->cost);
                decreaseKey(queue, neighbour->destination, updated_cost);
            }
            neighbour = neighbour->next;
        }
    }
}

void shortestPathTo(Graph *graph, int node, route_type* routes, bool connected)
{
    PrioQueue *queue; 
    if (graph && routes)
    {   
        // Early exit if node is completely disconnected
        if (!graph->lists[node]) return;

        // Create priority queue
        queue = createPrioQueue(EDGE_TYPES, graph->V);

        dijkstra(graph, node, queue, routes, connected);   

        // Free up resources
        deletePrioQueue(&queue);
    }
}


void printStatistics(Graph *graph, bool connected, bool verbose)
{
    int i, j;
    PrioQueue *queue;
    route_type *routes;

    int num_route_types[ROUTE_TYPES] = {0};
    int total = 0;

    if (graph)
    {
        queue = createPrioQueue(EDGE_TYPES, graph->V);
        routes = (route_type*) malloc(sizeof(route_type) * graph->V);
        assert(routes);

        for (i = 0; i < graph->V; i++)
        {
            // Only check nodes that are not completely disconnected
            if (graph->lists[i])
            {
                dijkstra(graph, i, queue, routes, connected);    
                
                for (j = 0; j < graph->V; j++)
                {
                    if (j != i && graph->lists[j])
                    {
                        num_route_types[routes[j]]++;
                        total++;
                    }
                }

                initPrioQueue(queue);
            }
            if (verbose) printf("\rWorking: %.2f%%", (i * 100.0) / (1.0 * graph->V));
        }

        printf("\nRoutes\n\tCustomer:\t%d\n\tPeer:\t\t%d\n\tProvider:\t%d\n\tTotal:\t\t%d\n",
            num_route_types[C], num_route_types[R], num_route_types[P], total);

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