n, d = (int(x) for x in input().split())
l = [int(x) for x in input().split()]
length = len(l)
new = [0 for x in l]
for i in range(length):
    o = i-d
    new[o]=str(l[i])
print(" ".join(new))
