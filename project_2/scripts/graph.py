import prio_dict

class Graph:

    def __init__(self):
        self.vertices = {}

    def __str__(self):
        return str([key for key in self.vertices.keys()])

    def __iter__(self):
        return iter(self.vertices.values())

    def add_vertex(self, node):
        self.vertices[node] = {}

    def get_vertex(self, node):
        if node in self.vertices:
            return self.vertices[node]
        else:
            return None

    def get_vertices(self):
        return self.vertices.keys()

    def add_edge(self, src, dst, weight=0):
        if src not in self.vertices:
            self.add_vertex(src)
        if dst not in self.vertices:
            self.add_vertex(dst)

        self.vertices[src][dst] = weight

    def find_path(self, src, dst, path=None):

        if path is None:
            path = []

        graph = self.vertices
        path = path + [src]

        if src == dst:
            return path
        if src not in graph:
            return None

        for v in graph[src]:
            if v not in path:
                temp = self.find_path(v, dst, path)
                if temp:
                    return temp
        return None

    def find_all_paths(self, src, dst, path=None):

        if path is None:
            path = []

        graph = self.vertices
        path = path + [src]

        if src == dst:
            return [path]
        if src not in graph:
            return []

        paths = []

        for v in graph[src]:
            if v not in path:
                temp = self.find_all_paths(v, dst, path)
                for p in temp:
                    paths.append(p)
        return paths

    def find_shortest_path(self, src, dst, path=None):

        if path is None:
            path = []

        graph = self.vertices
        path = path + [src]

        if src == dst:
            return path
        if src not in graph:
            return None

        shortest_path = None

        for v in graph[src]:
            if v not in path:
                temp = self.find_shortest_path(v, dst, path)
                if temp:
                    if not shortest_path or len(temp) < len(shortest_path):
                        shortest_path = temp

        return shortest_path

    def is_connected(self, visited=None, src=None):

        if visited is None:
            visited = set()

        graph = self.vertices
        vertices = list(graph.keys())

        if src is None:
            src = vertices[0]
        visited.add(src)

        if len(visited) != len(vertices):
            for v in graph[src]:
                if v not in visited:
                    if self.is_connected(visited, v):
                        return True
        else:
            return True

        return False


    def Dijkstra(self, G, src, dst=None):

        D = {}
        P = {}
        Q = prio_dict.PriorityDictionary()
        Q[src] = 0

        for v in Q:
            D[v] = Q[v]
            if v == dst:
                break
            for w in G[v]:
                vw_length = D[v] + G[v][w]
                if w in D:
                    if vw_length < D[w]:
                        raise ValueError
                elif w not in Q or vw_length < Q[w]:
                    Q[w] = vw_length
                    P[w] = v
        return (D,P)

    def shortest_path(self, G, src, dst):
        D,P = self.Dijkstra(G, src, dst)
        path = []
        while True:
            path.append(dst)
            if dst == src:
                break
            dst = P[dst]
        path.reverse()
        return path