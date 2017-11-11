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
		Q = PriorityDictionary()
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


class PriorityDictionary(dict):

	def __init__(self):
		self.heap = []
		dict.__init__(self)

	def smallest(self):

		if len(self) == 0:
			raise IndexError
		heap = self.heap

		while heap[0][1] not in self or self[heap[0][1]] != heap[0][0]:

			last_item = heap.pop()
			insertion_point = 0

			while True:

				small_child = 2*insertion_point + 1

				if small_child+1 < len(heap) and heap[small_child] > heap[small_child+1]:
					small_child += 1
				if small_child >= len(heap) or last_item <= heap[small_child]:
					heap[insertion_point] = last_item
					break
				heap[insertion_point] = heap[small_child]
				insertion_point = small_child

		return heap[0][1]

	def __iter__(self):
		def iterfn():
			while len(self) > 0:
				x = self.smallest()
				yield x
				del self[x]
		return iterfn()

	def __setitem__(self, key, val):
		dict.__setitem__(self, key, val)
		heap = self.heap

		if len(heap) > 2*len(self):
			self.heap = [(v,k) for k,v in self.iteritems()]
			self.heap.sort()
		else:
			new_pair = (val, key)
			insertion_point = len(heap)
			heap.append(None)
			while insertion_point > 0 and new_pair < heap[(insertion_point-1)//2]:
				heap[insertion_point] = heap[(insertion_point-1)//2]
				insertion_point = (insertion_point-1)//2
			heap[insertion_point] = new_pair

	def setdefault(self, key, val):
		if key not in self:
			self[key] = val
		return self[key]

	def update(self, other):
		for key in other.keys():
			self[key] = other[key]





if __name__ == '__main__':

	g = Graph()

	f = open("test3.txt", "r")
	data = f.readlines()

	for line in data:
		words = line.split()
		g.add_edge(int(words[0]), int(words[1]), int(words[2]))

	'''
	print(g)
	print(g.get_vertices())

	for u in g:
		print('%s' % (g.vertices[u.get_id()]))

	for u in g:
		for v in u.get_neighbors():
			print('(%s , %s , %s)' % (u.get_id(), v.get_id(), u.get_weight(v)))

	'''

	#print("find_all_paths = ", g.find_all_paths(1, 7))
	#print("find_path = ", g.find_path(1, 7))
	#print("find_shortest_path = ", g.find_shortest_path(1, 7))
	#print("is_connected = ", g.is_connected())
	print("shortest_path = ", g.shortest_path(g.vertices, 23123, 2312))






