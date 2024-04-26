MOD = 10**9 + 9
def compute_catalan(N):
    global MOD
    catalan = [0]*(N+1)
    catalan[0] = 1
    for i in range(1, N):
        for j in range(i):
            catalan[i] += catalan[j]*catalan[i-j-1]
        catalan[i] %= MOD
    return catalan
def generate_counts(catalan, N):
    counts = [[[0]*2 for j in range(N)] for i in range(N+1)]
    for i in range(1,N+1):
        for j in range(i):
            counts[i][j][0] += catalan[j]*catalan[i-j-1]
            counts[i][j][0] %= MOD
            for k in range(j):
                counts[i][k][0] += counts[j][k][1]*catalan[i-j-1]
                counts[i][k][1] += counts[j][k][0]*catalan[i-j-1]
                counts[i][k][0] %= MOD
                counts[i][k][1] %= MOD
            for k in range(j+1,i):
                counts[i][k][0] += counts[i-j-1][i-k-1][1]*catalan[j]
                counts[i][k][1] += counts[i-j-1][i-k-1][0]*catalan[j]
                counts[i][k][0] %= MOD
                counts[i][k][1] %= MOD
    return counts
catalan = compute_catalan(150)
T = int(input())
for test_case in range(T):
    N = int(input())
    alpha, beta = (int(x) for x in input().split())
    arr = [int(x) for x in input().split()]
    arr = sorted(arr)
    res = generate_counts(catalan,N)
    s = 0
    for i in range(N):
        s += (alpha*res[N][i][0] - beta*res[N][i][1])*arr[i]
        s %= MOD
    print(s)
