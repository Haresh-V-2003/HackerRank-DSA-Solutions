#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOR(i, a, b) for(__typeof(a) i=(a); i<(b); i++)
#define MEM(x,val) memset((x),(val),sizeof(x));
#define MOD 1000000009
#define N 100000
#define K 26


typedef long long ll;

char* readline();
char** split_string(char*);

void print_matrix(int n, int m, ll arr[n][m]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%lld ", arr[i][j]);
        }
        putchar('\n');
    }
}

ll cdp[K+1][K+1];

ll comb(ll n, ll k){
    if(k > n) return 0;
    if(n == k) return 1;
    if(k == 0) return 1;
    if(k == 1) return n % MOD;
    if(cdp[n][k]==-1) cdp[n][k] = ( comb(n-1,k-1) + comb(n-1,k) ) % MOD;
    return cdp[n][k];
}

ll dp[N+1][K+1];

void init() {
    MEM(cdp, -1);
    
    FOR(k, 1, K+1) {
        FOR(n, 1, N+1) { 
            if(n==1) dp[n][k] = k; 
            else {
                dp[n][k] = (n % 2 ? (dp[n-1][k]*k)%MOD: 
                                    (dp[n-1][k]*k)%MOD - dp[n/2][k]
                            ) % MOD;
                if(dp[n][k] < 0) dp[n][k] += MOD;
                
            }
        }
    }

    FOR(k, 1, K+1) {
        ll kN = 1;
        FOR(n, 1, N+1) { 
            kN = kN*k % MOD;
            dp[n][k] = kN - dp[n][k];
            if(dp[n][k] < 0) dp[n][k] += MOD;
            FOR(j, 1, k) { 
                dp[n][k] -= (dp[n][j]*comb(k,j)) % MOD;
                if(dp[n][k] < 0) dp[n][k] += MOD;
            }
        }
    }
    
}

int main()
{
    init();
    
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);
        assert(1 <= n && n <= 100000);
        assert(1 <= k && k <= 26);
        fprintf(fptr, "%lld\n", (dp[n][k]*comb(26,k))%MOD);
    }

    fclose(fptr);
}
