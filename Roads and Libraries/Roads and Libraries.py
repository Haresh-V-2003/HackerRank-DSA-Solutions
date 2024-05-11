from collections import defaultdict
from collections import deque

from math import pi,cos,sin

class graph:
    def __init__(self):
        self.nodes = []
        self.edges = defaultdict(set)
    def clone(self):
        g = graph()
        g.nodes = self.nodes[:]
        for n in self.nodes:
            for e in self.edges[n]:
                g.edges[n].add(e)
        return g

def count_clusters(g):
    nclust = 0
    used = set()
    n = len(g.nodes)

    csize = []
    
    for node in g.nodes:
        if node in used: continue
        used.add(node)

        size = 1
        Q = deque()
        Q.appendleft(node)
        while Q:
            cur = Q.pop()
            for neigh in g.edges[cur]:
                if neigh in used: continue
                used.add(neigh)
                Q.appendleft(neigh)
                size += 1
        nclust += 1
        csize.append(size)

    return nclust,csize

q = int(input())


for _ in range(q):
    n,m,clib,croad = [int(x) for x in input().split()]
    edges = [[int(x) for x in input().split()] for _ in range(m)]

    if clib < croad:
        print(clib*n)
        continue
    
    g = graph()
    g.nodes = range(1,n+1)
    for a,b in edges:
        g.edges[a].add(b)
        g.edges[b].add(a)

    nc,cs = count_clusters(g)
    print(nc*clib + sum((x-1)*croad for x in cs))
