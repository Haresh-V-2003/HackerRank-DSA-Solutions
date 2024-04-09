tree = [False, {}]

def add(word) :
    current = tree
    for c in word :
        try :
            current = current[1][c]
        except KeyError :
            current[1][c] = [False, {}]
            current = current[1][c]
    current[0] = True
    
def count(word) :
    count = 0
    for start in range(len(word)) :
        current, index = tree, start
        while True :
            if current[0] :
                count += 1
            try :
                current = current[1][word[index]]
                index += 1
            except (KeyError, IndexError) :
                break
    return count
    
v = 1
for x in range(801) :
    add(str(v)[::-1])
    v <<= 1

Done = {}    
T = int(input())
for t in range(T) :
    A = input()
    if not A in Done :
        Done[A] = count(A[::-1])
    print(Done[A])
