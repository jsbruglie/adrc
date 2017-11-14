/**
 * @file graph.c
 * @brief Graph implementation
 * 
 * @author Nuno Venturinha
 * @author João Borrego
 */

#include "graph.h"

/**
 * @brief Matrix for calculating a resulting route type
 * 
 * Outputs the resulting route type for a given
 * - type of edge that leads to the destination node
 * - type of current route so far
 */
RouteType ROUTE_TYPE_MATRIX[EDGE_TYPES][ROUTE_TYPES] =
{
    { P, P, P, I}, // Notice that the first and last row were swapped.
    { R, I, I, I}, // This is a simple trick to avoid additional verifications
    { C, I, I, I}  // or manually swapping the edge types in the graph itself.
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

RouteType selectionOp(EdgeType edge_type, RouteType route_type)
{
    return ROUTE_TYPE_MATRIX[edge_type][route_type];
}

void dijkstra(Graph *graph, int node, PrioQueue *queue, RouteType* routes, bool connected)
{
    int i;
    QueueNode *min;
    AdjListNode *neighbour;
    // If a route is comercially connected every node is reachable
    RouteType initial_cost = (connected)? P : I; 
    RouteType updated_cost;

    // Initialise the route type array
    for (i = 0; i < graph->V; i++)
        routes[i] = initial_cost;
    
    // Decrease the cost of the destination node in queue
    decreaseKey(queue, node, (int) C);

    // Main Dijkstra's algorithm loop
    for (i = 0; i < graph->V; i++)
    {
        min = getMaxPriority(queue);
        assert(min);
        routes[min->v] = min->cost;

        // Early exit if extracted unreachable node
        if (min->cost == I) break;
        // Early exit if network is strongly connected and a node with a provider route is extracted
        // This is a very important optimization and greatly improves run time!
        if (connected && min->cost == P) break;

        // Explore extracted node's neighbours
        neighbour = graph->lists[min->v];
        while (neighbour)
        {   
            // If neighbour has not been extracted from priority queue
            if (routes[neighbour->destination] == initial_cost)
            {
                updated_cost = selectionOp((EdgeType) neighbour->type, (RouteType) min->cost);
                decreaseKey(queue, neighbour->destination, updated_cost);
            }
            neighbour = neighbour->next;
        }
    }
}

void shortestPathTo(Graph *graph, int node, RouteType* routes, bool connected)
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
    RouteType *routes;

    int num_RouteTypes[ROUTE_TYPES] = {0};
    int total = 0;

    if (graph)
    {
        queue = createPrioQueue(EDGE_TYPES, graph->V);
        routes = (RouteType*) malloc(sizeof(RouteType) * graph->V);
        assert(routes);

        for (i = 0; i < graph->V; i++)
        {
            // Only check nodes that have connections and are not completely detached
            if (graph->lists[i])
            {
                dijkstra(graph, i, queue, routes, connected);    
                
                for (j = 0; j < graph->V; j++)
                {
                    // Do not count route-to-self or detached nodes' routes
                    if (j != i && graph->lists[j])
                    {
                        // Increment respective route type counter
                        num_RouteTypes[routes[j]]++;
                        total++;
                    }
                }
                // Re-initialize priority queue for reuse in next iteration
                initPrioQueue(queue);
            }
            if (verbose) printf("\rWorking: %.2f%%", (i * 100.0) / (1.0 * graph->V));
        }

        printf("Routes\n\tCustomer:\t%d\n\tPeer:\t\t%d\n\tProvider:\t%d\n\tTotal:\t\t%d\n",
            num_RouteTypes[C], num_RouteTypes[R], num_RouteTypes[P], total);

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