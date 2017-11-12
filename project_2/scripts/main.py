#!/usr/bin/python

import sys
import graph

def printUsage():
    print('main.py <graph_file>')

if __name__ == '__main__':

    if (len(sys.argv) != 2):
        printUsage()

    # Open input file
    f = open(sys.argv[1], "r")
    data = f.readlines()
    
    # Fill graph with edges in file
    g = graph.Graph()
    for line in data:
        src, dst, cost = line.split()
        g.add_edge(int(src), int(dst), int(cost))

    # Tests
    
    '''
    print(g)
    print(g.get_vertices())

    for u in g:
        print('%s' % (g.vertices[u.get_id()]))

    for u in g:
        for v in u.get_neighbors():
            print('(%s , %s , %s)' % (u.get_id(), v.get_id(), u.get_weight(v)))

    print("find_all_paths = ", g.find_all_paths(1, 7))
    print("find_path = ", g.find_path(1, 7))
    print("find_shortest_path = ", g.find_shortest_path(1, 7))
    print("is_connected = ", g.is_connected())
    ''' 
    
    print("shortest_path = ", g.shortest_path(g.vertices, 3, 2))