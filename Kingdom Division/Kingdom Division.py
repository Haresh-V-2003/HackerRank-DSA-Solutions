#!/bin/python3

import math
import os
import random
import re
import sys


def countColorings(root):
    v = {}
    for depth, node in d:
        if len(t[node]) == 0:
            v[(node, True)] = 1
            v[(node, False)] = 0
        else:
            cases = 1
            invalid = 1
            for child in t[node]:
                cases *= v[(child, True)] + v[(child, False)]
                invalid *= v[(child, False)]
            v[(node, True)] = cases
            v[(node, False)] = cases - invalid
    return v[(root, False)] * 2


def spanningTree(root):
    stack = [(root, 0)]
    while stack:
        node, depth = stack.pop()
        t[node] = set()
        d.append((depth, node))
        for adj in g[node]:
            if adj not in t:
                t[node].add(adj)
                stack.append((adj, depth + 1))


def kingdomDivision(n, roads):
    global g
    g = {}
    for road in roads:
        if road[0] in g:
            g[road[0]].add(road[1])
        else:
            g[road[0]] = {road[1]}
        if road[1] in g:
            g[road[1]].add(road[0])
        else:
            g[road[1]] = {road[0]}
    global t
    t = {}
    global d
    d = []
    spanningTree(n // 2)
    d.sort(reverse=True)
    return countColorings(n // 2) % (10 ** 9 + 7)


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    roads = []

    for _ in range(n-1):
        roads.append(list(map(int, input().rstrip().split())))

    result = kingdomDivision(n, roads)

    fptr.write(str(result) + '\n')

    fptr.close()
