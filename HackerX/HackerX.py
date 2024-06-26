n=int(input())
inp=(map(int,input().split())for i in range(n))
p=sorted(list((a+b,a-b)for a,b in inp))
a=list(y for x,y in p)
d=[]
for x in a:
    low,high=-1, len(d)
    while high-low>1:
        mid=(low+high)>>1
        if d[mid]>x:
            low=mid
        else:
            high=mid
    if high==len(d):
        d.append(x)
    else:
        d[high]=x
print(len(d))
