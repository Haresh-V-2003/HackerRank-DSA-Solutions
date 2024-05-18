# Enter your code here. Read input from STDIN. Print output to STDOUT
n,m=map(int,input().split())
roads=[]
dic={}
for i in range(m):
    [x,y]=list(map(int,input().split()))
    roads.append([x,y])
    if not x in dic:dic[x]={y}
    if x in dic:dic[x].add(y)
    if not y in dic:dic[y]={x}
    if y in dic:dic[y].add(x)
count=[0]*(n+1)
for x in dic:
    count[x]=len(dic[x])
_,start=min([[count[z],z] for z in dic],key=lambda a:a[0])
path=[start]
x=start
for i in range(1,n):
    if len(dic[x])==0:break
    _,y=min([[count[z],z] for z in dic[x]],key=lambda a:a[0])
    if x in dic[y]: dic[y].remove(x)
    count[y]-=1
    path.append(y)
    x=y
        
print(len(path))
print(*path, sep=" ")
