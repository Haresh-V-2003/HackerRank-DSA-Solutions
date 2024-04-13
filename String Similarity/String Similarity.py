#!/bin/python3

import sys

def stringSimilarity(s):
    # Complete this function
    result = length = len(s)
    right = 0
    left = 0
    z = [length]
  
    for i in range(1, length):
        z.append(0)
        if i <= right:
            z[i] = min(right - i + 1, z[i - left])
        while i + z[i] < length and s[z[i]] == s[i + z[i]]:
            z[i] += 1
        if i + z[i] - 1 > right:
            left = i
            right = i + z[i] - 1
        
        result += z[i]
    
    return result

if __name__ == "__main__":
    t = int(input().strip())
    for a0 in range(t):
        s = input().strip()
        result = stringSimilarity(s)
        print(result)
