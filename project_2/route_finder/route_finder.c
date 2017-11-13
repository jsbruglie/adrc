#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct AdjListNode_t
{
    int dest;
    int type;
    struct AdjListNode_t *next;
} AdjListNode;

typedef struct Graph_t
{
    int V;
    int **elected_route;
    AdjListNode **list;
} Graph;

typedef struct StackNode_t
{
    int vertex;
    struct StackNode_t *next;
} StackNode;

StackNode *create_stack_node(int vertex)
{
    StackNode *node = (StackNode *) malloc(sizeof(StackNode));

    node->vertex = vertex;
    node->next = NULL;

    return node;
}

int is_empty(StackNode *root)
{
    return !root;
}

void push(StackNode **root, int vertex)
{
    StackNode *node = create_stack_node(vertex);

    node->next = *root;
    *root = node;
}

int pop(StackNode **root)
{
    if(is_empty(*root))
    {
        return -1;
    }

    StackNode *temp = *root;
    *root = (*root)->next;

    int popped = temp->vertex;

    free(temp);

    return popped;
}


void shortest_path(Graph *graph, int src)
{

    int *visited;
    int vertex;
    int *routes;

    visited = (int *) malloc((graph->V)*sizeof(int));
    routes = (int *) malloc((graph->V)*sizeof(int));
    for(int i = 1; i < graph->V; i++)
    {
        routes[i] = (graph->list[i] != NULL) ? INT_MAX : 0;
        visited[i] = 0;
    }

    StackNode *customer = NULL;
    StackNode *peer = NULL;
    StackNode *provider = NULL;

    AdjListNode *curr = graph->list[src];
    while(curr != NULL)
    {
        switch(curr->type)
        {
            case 1:
                push(&customer, curr->dest);
                break;
            case 2:
                push(&peer, curr->dest);
                break;
            case 3:
                push(&provider, curr->dest);
                break;
            default:
                break;
        }
        curr = curr->next;
    }

    LOOP:
    while(provider != NULL)
    {
        vertex = pop(&provider);
        if(vertex != -1 && visited[vertex] == 0)
        {
            visited[vertex] = 1;
            routes[vertex] = 3;
            curr = graph->list[vertex];
            while(curr != NULL)
            {
                if(visited[curr->dest] == 0)
                {
                    switch(curr->type)
                    {
                        case 1:
                            push(&customer, curr->dest);
                            break;
                        case 2:
                            push(&peer, curr->dest);
                            break;
                        case 3:
                            push(&provider, curr->dest);
                            break;
                        default:
                            break;
                    }
                }
                curr = curr->next;
            }
        }
        goto LOOP;
    }
    while(peer != NULL)
    {
        vertex = pop(&peer);
        if(vertex != -1 && visited[vertex] == 0)
        {
            visited[vertex] = 1;
            routes[vertex] = 2;
            curr = graph->list[vertex];
            while(curr != NULL)
            {
                if(visited[curr->dest] == 0)
                {
                    switch(curr->type)
                    {
                        case 1:
                            push(&customer, curr->dest);
                            break;
                        default:
                            break;
                    }
                }
                curr = curr->next;
            }
        }
        goto LOOP;
    }
    while(customer != NULL)
    {
        vertex = pop(&customer);
        if(vertex != -1 && visited[vertex] == 0)
        {
            visited[vertex] = 1;
            routes[vertex] = 1;
            curr = graph->list[vertex];
            while(curr != NULL)
            {
                if(visited[curr->dest] == 0)
                {
                    switch(curr->type)
                    {
                        case 1:
                            push(&customer, curr->dest);
                            break;
                        default:
                            break;
                    }
                }
                curr = curr->next;
            }
        }
        goto LOOP;
    }


    for(int i = 1; i < graph->V; i++)
    {
        if(i != src)
        {
            /*
            switch(routes[i])
            {
                case 1:
                    fprintf(stdout, "%d uses provider route to %d\n", i, src);
                    break;
                case 2:
                    fprintf(stdout, "%d uses peer route to %d\n", i, src);
                    break;
                case 3:
                    fprintf(stdout, "%d uses customer route to %d\n", i, src);
                    break;
                case INT_MAX:
                    fprintf(stdout, "%d has no route to %d\n", i, src);
                    break;
                default:
                    break;
            }
            */
            if(routes[i] != 0 && routes[i] != INT_MAX)
                fprintf(stdout, "%d %d %d\n", i, routes[i], src);
        }
    }

    free(visited);
    free(routes);
}

AdjListNode *create_node(int dest, int type)
{
    AdjListNode *node = (AdjListNode *) malloc(sizeof(AdjListNode));

    node->dest = dest;
    node->type = type;
    node->next = NULL;

    return node;
}

Graph *create_graph(int V)
{
    Graph *graph = (Graph *) malloc(sizeof(Graph));

    graph->V = V+1;

    graph->list = (AdjListNode **) malloc((graph->V) * sizeof(AdjListNode*));

    for(int i = 0; i < graph->V; i++)
    {
        graph->list[i] = NULL;
    }

    return graph;
}

void add_edge(Graph *graph, int src, int dest, int type)
{
    AdjListNode *node = create_node(dest, type);
    node->next = graph->list[src];
    graph->list[src] = node;
}


Graph *create_graph_from_file(char *filename)
{
    Graph *graph = NULL;
    FILE *file = fopen(filename, "r");

    int highest_id  = 0;
    int node_id     = 0;
    int src         = 0;
    int dest        = 0;
    int type        = 0;

    while(fscanf(file, "%d", &node_id) == 1)
    {
        if(node_id > highest_id)
        {
            highest_id = node_id;
        }
    }

    rewind(file);

    graph = create_graph(highest_id);

    while(fscanf(file, "%d %d %d", &src, &dest, &type) == 3)
    {
        add_edge(graph, src, dest, type);
    }

    fclose(file);

    return graph;
}

void print_graph(Graph *graph)
{
    AdjListNode *curr;

    for(int i = 0; i < graph->V; i++)
    {
        curr = graph->list[i];
        while(curr != NULL)
        {
            fprintf(stdout, "%d->(%d)->%d\n", i, curr->type, curr->dest);
            curr = curr->next;
        }
    }
}

void destroy_graph(Graph **graph_ptr)
{
    int i;
    AdjListNode *cur, *next;
    Graph *graph = *graph_ptr;

    if (graph)
    {
        for (i = 0; i < graph->V; i++)
        {
            cur = graph->list[i];
            while (cur)
            {
                next = cur->next;
                free(cur);
                cur = next;
            }
            graph->list[i] = NULL;
        }
        free(graph->list);
        free(graph);
    }
    *graph_ptr = NULL;
}




int main(int argc, char **argv)
{
    Graph *graph;

    graph = create_graph_from_file(argv[1]);

    /*
    for(int i = 1; i < 200; i++)
    {
        shortest_path(graph, i);
    }
    */

    shortest_path(graph, 1234);
    destroy_graph(&graph);
}






























