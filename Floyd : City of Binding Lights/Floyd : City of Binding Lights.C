#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define d(...) // fprintf(stderr, __VA_ARGS__)

int main() {
    int nv, ne;
    scanf("%d %d", &nv, &ne);
    unsigned dist[nv][nv];
    memset(dist, 0xff, sizeof(unsigned) * nv * nv);
    for (int k = 0; k != nv; ++k) {
        dist[k][k] = 0;
    }
    while (ne--) {
        int a,b,w;
        scanf("%d %d %d", &a, &b, &w);
        dist[a-1][b-1] = w;
    }
    for (int k = 0; k != nv; ++k) {
        for (int i = 0; i != nv; ++i) {
            for (int j = 0; j != nv; ++j) {
                if (dist[i][j] > (long) dist[i][k] + dist[k][j]) {
                    d("%u > %u + %u\n", dist[i][j], dist[i][k], dist[k][j]);
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    int nq;
    scanf("%d", &nq);
    while (nq--) {
        int a,b;
        scanf("%d %d", &a, &b);
        d("Query %d -> %d\n", a, b);
        printf("%d\n", dist[a-1][b-1]);
    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
