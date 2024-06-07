#!/bin/python3

import sys
from collections import defaultdict
from collections import deque

import heapq

def min_path(graph, n):
       
    costs = [10 ** 10] * (n + 1)
    work = []
    heapq.heappush(work, (0, 1))
    
    costs[1] = 0
    
    while work:
        (current_cost, current_node) = heapq.heappop(work)
        for (neighbour, cost) in graph[current_node]:
            acc_cost = max(current_cost, cost)
            if acc_cost < costs[neighbour]:
                costs[neighbour] = acc_cost
                heapq.heappush(work, (acc_cost, neighbour))
    
    return costs[n] if costs[n] < 10 ** 10 else 'NO PATH EXISTS'

if __name__ == '__main__':
    g_nodes, g_edges = map(int, input().split())
    
    graph = defaultdict(set)
    
    for _ in range(g_edges):
        start, end, cost = map(int, input().split())
        graph[start].add((end, cost))
        graph[end].add((start, cost))

    print(min_path(graph, g_nodes))
