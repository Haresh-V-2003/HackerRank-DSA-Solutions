T = int(input())

def alpha_min(a, b):
    la = len(a)
    lb = len(b)
    a += "z"
    b += "z"
    i = j = 0
    res = ""
    while (i != la and j != lb):
        if a[i:] < b[j:]:
            res += a[i]
            i += 1
        else:
            res += b[j]
            j += 1
        
    res += a[i: -1] + b[j: -1]
    return res
    
for _ in range(T):
    
    a = input().strip()
    b = input().strip()
    print(alpha_min(a, b))
