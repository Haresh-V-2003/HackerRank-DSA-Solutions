n = int(input())
hashmap = {}

for i in range(n):
    string = input()
    hashmap[string] = 1 if string not in hashmap else hashmap[string] + 1

q = int(input())

for j in range(q):
    string = input()
    print(0 if string not in hashmap else hashmap[string])
