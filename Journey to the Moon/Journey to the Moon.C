#include<stdio.h>
#include<stdlib.h>

// search for root of p.
long long int Find(long long int *uf, long long int p)
{
    while (p != uf[p])
        p = uf[p];
    return p;
}

// Use Union to link p and q to root of tree.
void Union(long long int *uf, int *sz, long long int p, long long int q, int *count)
{
    long long int pRoot = Find(uf, p);
    long long int qRoot = Find(uf, q);

    if (pRoot == qRoot)
        return;

    if (sz[pRoot] < sz[qRoot]) {
        uf[pRoot] = qRoot;
        sz[qRoot] += sz[pRoot];
    }
    else {
        uf[qRoot] = pRoot;
        sz[pRoot] += sz[qRoot];
    }
    (*count)--;
}

int main()
{
    int n, l;
    scanf("%d%d", &n, &l);
    if (n == 1)
    {
        printf("0\n");
        return(0);
    }
    long long int **pairs = (long long int**)malloc(sizeof(int*)*l);
    for (int i = 0; i < l; i++) {
        pairs[i] = (long long int*)calloc(2, sizeof(long long int));
        scanf("%lld %lld", &pairs[i][0], &pairs[i][1]);
    }

    long long int ans = 0;

    /** Write code to compute answer using n,l,pairs**/

    long long int *uf = (long long int *)malloc(n * sizeof(long long int));
    int *sz = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        uf[i] = i;
        sz[i] = 1;
    }

    int count = n; // Keep track of number of roots or separate trees
    for (int i = 0; i < l; i++) {
        Union(uf, sz, pairs[i][0], pairs[i][1], &count);
    }

    // Find all roots and count the number of connection to root.
    for (long long int i = 0; i < n; i++) {
        sz[i] = 0;
    }
    for (long long int i = 0; i < n; i++) {
        int p = Find(uf, i);
        // uf[i] is not root but we searched to fidn root.
        // increment count for root of tree which contains ith entry.
        sz[p]++;
    }

    int *sums = (int *)malloc(n * sizeof(int));
    for (long long int i = 0; i < n; i++) {
        sums[i] = 0;
    }
    int sum = 0;
    for (long long int i = n - 1; i >= 0; i--) {
        if (sz[i] > 0) {
            sums[i] = sum;
            sum += sz[i];
        }
    }
    ans = 0;
    for (int i = 0; i < n; i++) {
        // Search for countries.
        if (sz[i] > 0) {
            ans += (long long int)sz[i] * (long long int)sums[i];
        }
    }
    printf("%lld\n", ans);
    return(0);
}
