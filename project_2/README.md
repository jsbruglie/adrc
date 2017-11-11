### Graph representation

### Mathematical formulation

- a ⊕ b = min (a, b)
- Total order from ⊕ represented by ≽, such that for a ⊕ b = a we have a ≽ b.
- a ⊗ b should be read as edge of type *a*, traversing edge of type *b* results in a type a ⊗ b route.
The operator is given by the following table:

| ⊗ | C | R | P |
|---|---|---|---|
| C | C | • | • |
| R | R | • | • |
| P | P | P | P |

### i) Finding cycles

- It is possible to disregard every connection that is not between customer and provider.
This is due to the impossibility of cycles involving peer connections.
After a first peer connection it is impossible to traverse another peer edge.

- The best algorithm seems to be related to Tarjan's strongly connected components algorithm.
The core idea is that nodes have three possible states:
    + white or unvisited
    + grey or visited in the current path
    + black visited all the neighbours and node is done

- For every node in graph:
    + if node is white perform DFS
        - mark node as grey
        - visit its neihgbours
            - if a neighbour is grey, then a cycle is present
        - mark node as black
    + else if node is grey, then a cycle is present

Check [link](https://algocoding.wordpress.com/2015/04/02/detecting-cycles-in-a-directed-graph-with-dfs-python/).

### ii) Determine best path from every node to a given destination

- Perform an adapted inverted version of Dijkstra's algorithm.
Traditionally, Dijkstra will give you the shortest path tree for a given root node.
In this case we instead need the path **from all** nodes to a given root.
For this reason, we have to invert the search.

- Instead of changing the weight or properties of an edge, since the *cost* of a path is
mainly determined by the ⊗ operation, we can merely alter it to reflect the weight inversion.

- A traditional heap structure may not be needed, since there are only 3 possible different values
for the type of a path.

- It might be possible to avoid checking provider edges if we know whether the graph is conercially connected.

### iii) Statistics (Obtain types of best path from all nodes to every possible other node)

- Perform ii) for each node is an option.

### iv) Determine if graph is comercially connected

- [Serius doubts] It may be possible to solve the problem by:
    + Doing a DFS
    + Inverting connections
    + Repeating DFS
    + If any of the previous DFS's failed to visit every node, than the graph is **NOT** comercially connected.
    Otherwise, it is.

- Alternatively:
    + Determine which nodes are Tier-1, i.e., have only customers and no providers.
    + Check if every single one of the *n1* Tier-1 nodes is connected to the remaining ones by peer connections.
    This is *O(n1^2)* which should be reasonable if *n1* is small.  