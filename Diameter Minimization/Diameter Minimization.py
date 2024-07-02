#!/bin/python3


import sys
import math

def opt_diameter(n, m):
    count = 1
    depth = 0
    while count < n:
        depth += 1
        count = m ** depth
    return depth
    
def diameter(n, m):
    count = 1
    depth = 0
    while count < n:
        depth += 1
        count += m ** depth
    left_over = m ** depth - (count - n)
    limit = m ** (depth - 1)
    discount = 1
    if left_over > limit:
        discount = 0
    return max(depth, 2 * depth - discount)

def solve(in_file, out_file):
    n, m = (int(raw) for raw in in_file.readline().strip().split(' '))
    out_file.write("{}\n".format(opt_diameter(n, m)))
    count = 0
    for _ in range(n):
        ret = []
        for _ in range(m):
            val = count % n
            count += 1
            ret.append(str(val))
        out_file.write("{}\n".format(" ".join(ret)))

if __name__ == '__main__':
    from_file = False
    if from_file:
        path = 'Data\\'
        name = 'mega_prime'
        file_input = open(path + name + '.in', 'r')
        file_output = open(path + name + '.out','w')
        solve(file_input, file_output)
        file_input.close()
        file_output.close()
    else:
        solve(sys.stdin, sys.stdout)
