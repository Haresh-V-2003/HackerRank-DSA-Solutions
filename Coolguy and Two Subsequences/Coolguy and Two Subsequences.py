def smart():
    left = [0] * (n + 2)
    right = [0] * (n + 2)
    singles = pairs = 0
    ans = 0
    def remove(k):
        nonlocal singles, pairs
        s = k * (k + 1) // 2
        singles -= s
        pairs -= (k+2)*(k+1)*k*(k-1)//24 + s * singles
    def add(k):
        nonlocal singles, pairs
        s = k * (k + 1) // 2
        pairs += (k+2)*(k+1)*k*(k-1)//24 + s * singles
        singles += s
    for i in sorted(range(1, n+1), key=A.__getitem__)[::-1]:
        l, r = left[i-1], right[i+1]
        k = l + 1 + r
        right[i - l] = left[i + r] = k
        oldpairs = pairs
        remove(l)
        remove(r)
        add(k)
        ans += A[i] * (pairs - oldpairs)
    return ans % (10**9 + 7)

n = int(input())
A = [None] + list(map(int, input().split()))
print(smart())
