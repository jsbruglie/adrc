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