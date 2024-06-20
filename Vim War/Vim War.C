#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1048576
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int n, m, r, pos[25], ar[MAX], temp[MAX], P[MAX], dp[MAX][2];

int Solve(){
    int i, j, k, x, y, u, v, bitmask;

    clr(dp);
    for (i = 0; i < n; i++) dp[ar[i]][0]++;

    for (j = 1; j < 21; j++){
        u = j & 1;
        v = (j - 1) & 1;

        for (i = 0; i < MAX; i++){
            if (i & (1 << (j - 1))) dp[i][u] = dp[i][v];
            else dp[i][u] = (dp[i][v] + dp[i + (1 << (j - 1))][v]);
        }
    }

    int res = P[n];
    for (bitmask = 1; bitmask < MAX; bitmask++){
        x = dp[bitmask][0];
        if (x){
            if (__builtin_popcount(bitmask) & 1) res = (res - P[x] + MOD) % MOD;
            else res = (res + P[x]) % MOD;
        }
    }

    return res;
}

int main(){
    char str[25];
    int i, j, k, x, lim;

    P[0] = 1;
    for (i = 1; i < MAX; i++) P[i] = (P[i - 1] << 1) % MOD;
    for (i = 0; i < MAX; i++) P[i] = (P[i] - 1 + MOD) % MOD;

    while (scanf("%d %d", &n, &m) != EOF){
        for (i = 0; i <= n; i++){
            x = 0;
            scanf("%s", str);

            for (j = 0; str[j]; j++) x = (x << 1) + (str[j] - 48);
            temp[i] = x;
        }

        r = n;
        n = 0, k = 0;
        memset(pos, -1, sizeof(pos));

        for (j = 0; j < m; j++){
            if (temp[r] & (1 << j)) pos[j] = k++;
        }

        lim = (1 << k) - 1;
        for (i = 0; i < r; i++){
            x = 0, k = 0;
            for (j = 0; j < m; j++){
                if (temp[i] & (1 << j)){
                    if (pos[j] == -1){
                        k = 1;
                        break;
                    }
                    x |= (1 << pos[j]);
                }
            }
            if (!k) ar[n++] = x ^ lim;
        }

        printf("%d\n", Solve());
    }
    return 0;
}
