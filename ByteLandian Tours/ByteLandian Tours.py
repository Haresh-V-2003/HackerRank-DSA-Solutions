#!/bin/python3

import os
import sys
import math

#
# Complete the bytelandianTours function below.
#
def bytelandianTours(n, roads):
    if n <= 2:
        return 1
    m = 1000000007
    nbr = list()
    for i in range(n):
        nbr.append(list())
    for a,b in roads:
        nbr[a].append(b)
        nbr[b].append(a)
    
    city = 0
    if len(nbr[0]) == 1:
        city = nbr[0][0]
    nbr[city].sort(key=lambda x: len(nbr[x]), reverse = True)
    if len(nbr[nbr[city][0]]) == 1:
        return math.factorial(len(nbr[city])) % m
    if len(nbr[city]) > 2 and len(nbr[nbr[city][2]]) > 1:
        return 0
    if len(nbr[nbr[city][1]]) > 1:
        next_route = nbr[city][1]
        nbr[next_route].remove(city)
        rslt = (2 * math.factorial(len(nbr[city]) - 2)) % m
    else:
        next_route = -1
        rslt = (2 * math.factorial(len(nbr[city]) - 1)) % m
    #print(city, nbr)
    parent = city
    city = nbr[city][0]
    nbr[city].remove(parent)
    while True:
        nbr[city].sort(key=lambda x: len(nbr[x]), reverse = True)
        #print(city, nbr)
        if len(nbr[nbr[city][0]]) == 1:
            rslt = (rslt * (math.factorial(len(nbr[city])) %m)) %m
            if next_route != -1:
                city = next_route
                next_route = -1
                continue
            else:
                break
        if len(nbr[city]) > 1 and len(nbr[nbr[city][1]]) > 1:
            return 0
        rslt = (rslt * (math.factorial(len(nbr[city])-1) %m)) %m
        
        parent = city
        city = nbr[city][0]
        nbr[city].remove(parent)
        
    return rslt
    

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        n = int(input())

        roads = []

        for _ in range(n-1):
            roads.append(list(map(int, input().rstrip().split())))

        result = bytelandianTours(n, roads)

        fptr.write(str(result) + '\n')

    fptr.close()
