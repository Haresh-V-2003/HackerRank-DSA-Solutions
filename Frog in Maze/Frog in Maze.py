#!/bin/python3

import sys

from collections import deque

def ismine(char):
  return char == '*'

def isexit(char):
  return char == '%'

def isopen(char):
  return char == 'A' or char == 'O'

def isobstacle(char):
  return char == '#'

def probability(node):
  if ismine(node): # mine
    return 0.0
  if isexit(node): # exit
    return 1.0
  # if tunnel(node) != None: # tunnel

def getneighbs(node):
  # print("Getting neighbs for",node)
  global n,m,tunnels
  i0,j0 = node
  dirs = [(0,1),(1,0),(-1,0),(0,-1)]
  out = []
  for di, dj in dirs:
    i,j = i0+di, j0+dj
    if i < 0 or i >= n:
      continue
    if j < 0 or j >= m:
      continue
    if (i,j) in tunnels:
      i,j = tunnels[(i,j)]
    ch = mat[i][j]
    if isobstacle(ch):
      continue
    out.append(mapping[(i,j)])
  return out

def matmult(m, times): # m is square
  if times == 0:
    return m
  n = len(m)
  newm = [[sum(a*b for a,b in zip(X_row,Y_col) if a != 0 and b!= 0) for Y_col in zip(*m)] for X_row in m]
  return matmult(newm, times - 1)

n, m, k = map(int,input().strip().split(' '))
mat = [[None for _ in range(m)] for _ in range(n)]
mapping = {} # maps (i,j) to a row/col in our move matrix
reversemapping = {} # maps a node to (i,j)
MAP_MINE = -2
MAP_EXIT = -1
MAP_START = 0
next_open = 1

def pmat(m):
  return True
  print("---")
  for r in m:
    print(" ".join(["%0.2f"%v for v in r]))

def mygauss(m):
    #eliminate columns
    for col in range(len(m[0])):
        for row in range(col+1, len(m)):
            r = [(rowValue * (-(m[row][col] / m[col][col]))) for rowValue in m[col]]
            m[row] = [sum(pair) for pair in zip(m[row], r)]
    #now backsolve by substitution
    ans = []
    m.reverse() #makes it easier to backsolve
    for sol in range(len(m)):
            if sol == 0:
                ans.append(m[sol][-1] / m[sol][-2])
            else:
                inner = 0
                #substitute in all known coefficients
                for x in range(sol):
                    inner += (ans[x]*m[sol][-2-x])
                #the equation is now reduced to ax + b = c form
                #solve with (c - b) / a
                ans.append((m[sol][-1]-inner)/m[sol][-sol-2])
    ans.reverse()
    return ans
  
for i in range(n):
    row = input().strip()
    for j, char in enumerate(row):
      mat[i][j] = char
      if isobstacle(char):
        continue
      if char == 'A':
        node = MAP_START
        reversemapping[node] = (i,j)
      elif ismine(char):
        node = MAP_MINE
      elif isexit(char):
        node = MAP_EXIT
      else: # open
        node = next_open
        reversemapping[node] = (i,j)
        next_open += 1
      mapping[(i,j)] = node
#print(mapping)
tunnels = {}
for a0 in range(k):
    i1, j1, i2, j2 = map(lambda x: int(x) - 1, input().strip().split(' '))
    tunnels[(i1,j1)] = (i2,j2)
    tunnels[(i2,j2)] = (i1,j1)
nodes = next_open + 2
transitions = [[0 for _ in range(nodes)] for _ in range(nodes)] # transitions[i][j] is probability of ending up at j from i
transitions[MAP_MINE][MAP_MINE] = 1 # try zero to make it disappear from probailities
transitions[MAP_EXIT][MAP_EXIT] = 1
for i in range(nodes - 2):
  neighbs = getneighbs(reversemapping[i])
  opts = len(neighbs)
  if opts == 0:
    # leave at zero to make it disappear from the probabilities
    # transitions[i][i] = 1
    continue
  for j in neighbs:
    transitions[i][j] += 1 / opts
# make the transitions matrix all in upper-right quadrant (drive to the end)
for i in range(nodes):
  for j in range(nodes):
    if j < i: # back-transition, substitute that row here
      p = transitions[i][j]
      if p > 0:
        # print(i,j)
        transitions[i][j] = 0
        transitions[i] = [transitions[i][k] + p*transitions[j][k] for k in range(nodes)]
    if j == i and i < nodes-2: # move on, except end goals
      p = transitions[i][j]
      if p > 0: # if we get back to here, distribute that among the other probs
        transitions[i][j] = 0
        for k in range(j+1,nodes):
          if transitions[i][k] > 0:
            transitions[i][k] /= (1-p)
pmat(transitions)
# now fully cancel out row 0 except for endpoints
for i in range(1,nodes-2):
  p = transitions[0][i]
  if p > 0:
        transitions[0][i] = 0
        for k in range(i+1,nodes):
          transitions[0][k] += p*transitions[i][k]
    
# transitions = mygauss(transitions)
pmat(transitions)
print(transitions[0][MAP_EXIT])
