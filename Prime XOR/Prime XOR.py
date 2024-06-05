from collections import Counter
from math import sqrt
import re
import sys
import random
# Complete the primeXor function below.
def middle_out(counts):
    a = ((4096, 4351), (4352, 4500), (3584, 4095), (3500, 3583))
    b = ((256, 0), (512, 0), (512, 4096), (1024, 4096))
    divisor = 0
    count = [0]*4501
    for i,n in counts:
        count[i] = n

    sum = [[0]*8192 for _ in range(2)] 
    temp, update = 0, 1 
    sum[temp][0] = 1 
    divisor = 10**9 + 7
    for i,p in enumerate(a):
        for j,n in enumerate(count[p[0]:p[1]+1]):
            if n:
                temp2 = n//2 
                same = 1 + temp2
                change = (n+1)//2  
                o = b[i][1]
                for x in range(b[i][0]):  
                    y = x^(j+p[0])
                    sum[update][y] = (sum[temp][x]*change + sum[temp][y]*same)
                    sum[update][x] = (sum[temp][y]*change + sum[temp][x]*same)
                    
                    if o:
                        sum[update][y+o] = (sum[temp][x+o]*change + sum[temp][y+o]*same)
                        sum[update][x+o] = (sum[temp][y+o]*change + sum[temp][x+o]*same)
                        
                if sum[update][0] > 100000*divisor:  
                    for x in range(len(sum[update])):
                        sum[update][x] %= divisor
                temp, update = update, temp

    p = primes(8191)
    total = 0
    for prime in p:
        total += sum[temp][prime]
    return total % divisor

def primes(n):
    x = [True]*((n-1)//2)
    for i in range(int((sqrt(n)-3)//2)+1):
        if x[i]:
            x[2*i*i+6*i+3::2*i+3] = [False] * int((n-(2*i+3)**2)//(4*i+6)+1)
    return [2] + [2*i+3 for i,v in enumerate(x) if v]
q = int(input())
for _ in range(q):
    n = int(input())
    numbers = Counter(int(x) for x in input().split()).items()
    print(middle_out(numbers))
