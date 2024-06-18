#include<stdio.h>
#include<stdlib.h>
#define MOD 1000000000000000003LL
int N, M, mmst[100][100], *u, *v, *w, map[100];
long long aa[100][100][100][2];
unsigned long long CC(unsigned long long n, unsigned long long d)
{
    while(1)
    {
        n %= d;
        if( n == 0 )
        {
            return d;
        }
        d %= n;
        if( d == 0 )
        {
            return n;
        }
    }
}
void merge3(int *a, int *left_a, int *right_a, int *b, int *left_b, int *right_b, int *c, int *left_c, int *right_c, int left_size, int right_size)
{
    int i = 0, j = 0;
    while( i < left_size || j < right_size )
    {
        if( i == left_size )
        {
            a[i + j] = right_a[j];
            b[i + j] = right_b[j];
            c[i + j] = right_c[j];
            j++;
        }
        else if( j == right_size )
        {
            a[i + j] = left_a[i];
            b[i + j] = left_b[i];
            c[i + j] = left_c[i];
            i++;
        }
        else if( left_a[i] <= right_a[j] )
        {
            a[i + j] = left_a[i];
            b[i + j] = left_b[i];
            c[i + j] = left_c[i];
            i++;
        }
        else
        {
            a[i + j] = right_a[j];
            b[i + j] = right_b[j];
            c[i + j] = right_c[j];
            j++;
        }
    }
    return;
}
void sort_a3(int *a, int *b, int *c, int size)
{
    if( size < 2 )
    {
        return;
    }
    int m = ( size + 1 ) / 2, i;
    int *left_a, *left_b, *left_c, *right_a, *right_b, *right_c;
    left_a = (int*)malloc(m * sizeof(int));
    right_a = (int*)malloc(( size - m ) * sizeof(int));
    left_b = (int*)malloc(m * sizeof(int));
    right_b = (int*)malloc(( size - m ) * sizeof(int));
    left_c = (int*)malloc(m * sizeof(int));
    right_c = (int*)malloc(( size - m ) * sizeof(int));
    for( i = 0 ; i < m ; i++ )
    {
        left_a[i] = a[i];
        left_b[i] = b[i];
        left_c[i] = c[i];
    }
    for( i = 0 ; i < size - m ; i++ )
    {
        right_a[i] = a[i + m];
        right_b[i] = b[i + m];
        right_c[i] = c[i + m];
    }
    sort_a3(left_a, left_b, left_c, m);
    sort_a3(right_a, right_b, right_c, size - m);
    merge3(a, left_a, right_a, b, left_b, right_b, c, left_c, right_c, m, size - m);
    free(left_a);
    free(right_a);
    free(left_b);
    free(right_b);
    free(left_c);
    free(right_c);
    return;
}
long long mul(unsigned long long x, unsigned long long y)
{
    unsigned long long a, b, c, d, A, B, C;
    long long ans;
    int i;
    a = x / 1000000000;
    b = x % 1000000000;
    c = y / 1000000000;
    d = y % 1000000000;
    A = d * b % MOD;
    B = ( d * a + c * b ) % MOD;
    C = a * c % MOD;
    for( i = 0 ; i < 9 ; i++ )
    {
        B = B * 10 % MOD;
    }
    for( i = 0 ; i < 18 ; i++ )
    {
        C = C * 10 % MOD;
    }
    ans = ( A + B + C ) % MOD;
    return ans;
}
void lu(long long **a, long long **ml, long long **mu, long long **dl, long long **du, int n)
{
    int i = 0, j = 0, k = 0;
    long long t1, t2;
    for( i = 0 ; i < n ; i++ )
    {
        for( j = 0 ; j < n ; j++ )
        {
            if( j < i )
            {
                ml[j][i] = 0;
                dl[j][i] = 1;
            }
            else
            {
                ml[j][i] = a[j][i];
                dl[j][i] = 1;
                for( k = 0 ; k < i ; k++ )
                {
                    t1 = mul(ml[j][k], mu[k][i]);
                    t2 = mul(dl[j][k], du[k][i]);
                    ml[j][i] = ( mul(ml[j][i], t2) - mul(t1, dl[j][i]) + MOD ) % MOD;
                    dl[j][i] = mul(dl[j][i], t2);
                }
            }
        }
        for( j = 0 ; j < n ; j++ )
        {
            if( j < i )
            {
                mu[i][j] = 0;
                du[i][j] = 1;
            }
            else if( j == i )
            {
                mu[i][j] = 1;
                du[i][j] = 1;
            }
            else
            {
                mu[i][j] = mul(a[i][j], dl[i][i]);
                du[i][j] = ml[i][i];
                for( k = 0 ; k < i ; k++ )
                {
                    t1 = mul(mul(ml[i][k], mu[k][j]), dl[i][i]);
                    t2 = mul(mul(dl[i][k], du[k][j]), ml[i][i]);
                    mu[i][j] = ( mul(mu[i][j], t2) - mul(t1, du[i][j]) + MOD ) % MOD;
                    du[i][j] = mul(du[i][j], t2);
                }
            }
        }
    }
}
long long modInverse(long long a, long long mod)
{
    long long b0 = mod, t, q, x0 = 0, x1 = 1;
    while( a > 1 )
    {
        q = a / mod;
        t = mod;
        mod = a % mod;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if( x1 < 0 )
    {
        x1 += b0;
    }
    return x1;
}
long long det(long long **a, int n)
{
    long long **ml, **mu, **dl, **du, ans = 1;
    int i, j;
    ml = (long long**)malloc(n * sizeof(long long*));
    for( i = 0 ; i < n ; i++ )
    {
        ml[i] = (long long*)malloc(n * sizeof(long long));
    }
    mu = (long long**)malloc(n * sizeof(long long*));
    for( i = 0 ; i < n ; i++ )
    {
        mu[i] = (long long*)malloc(n * sizeof(long long));
    }
    dl = (long long**)malloc(n * sizeof(long long*));
    for( i = 0 ; i < n ; i++ )
    {
        dl[i] = (long long*)malloc(n * sizeof(long long));
    }
    du = (long long**)malloc(n * sizeof(long long*));
    for( i = 0 ; i < n ; i++ )
    {
        du[i] = (long long*)malloc(n * sizeof(long long));
    }
    for( i = 0 ; i < n ; i++ )
    {
        for( j = 0 ; j < n ; j++ )
        {
            ml[i][j] = mu[i][j] = 0;
            dl[i][j] = du[i][j] = 1;
            a[i][j] = ( a[i][j] + MOD ) % MOD;
        }
    }
    lu(a, ml, mu, dl, du, n);
    for( i = 0 ; i < n ; i++ )
    {
        ans = mul(mul(ans, ml[i][i]), modInverse(dl[i][i], MOD));
    }
    for( i = 0 ; i < n ; i++ )
    {
        free(ml[i]);
        free(mu[i]);
        free(dl[i]);
        free(du[i]);
    }
    free(ml);
    free(mu);
    free(dl);
    free(du);
    return ans;
}
unsigned long long MST()
{
    unsigned long long ans = 0;
    int i, j, p1, p2, p3, p4;
    for( i = 0 ; i < N ; i++ )
    {
        for( j = 0 ; j < N ; j++ )
        {
            mmst[i][j] = 0;
        }
    }
    int *p = (int*)malloc(N * sizeof(int));
    for( i = 0 ; i < N ; i++ )
    {
        p[i] = i;
    }
    for( i = 0 ; i < M ; i++ )
    {
        p1 = u[i] - 1;
        while( p[p1] != p1 )
        {
            p1 = p[p1];
        }
        p2 = v[i] - 1;
        while( p[p2] != p2 )
        {
            p2 = p[p2];
        }
        if( p1 != p2 )
        {
            ans += w[i];
            mmst[u[i] - 1][v[i] - 1] = 1;
            mmst[v[i] - 1][u[i] - 1] = 1;
        }
        p3 = u[i] - 1;
        while(1)
        {
            if( p[p3] == p3 )
            {
                p[p3] = p1;
                break;
            }
            p4 = p3;
            p3 = p[p3];
            p[p4] = p1;
        }
        p3 = v[i] - 1;
        while(1)
        {
            if( p[p3] == p3 )
            {
                p[p3] = p1;
                break;
            }
            p4 = p3;
            p3 = p[p3];
            p[p4] = p1;
        }
    }
    free(p);
    return ans;
}
void dfs(int x, int p)
{
    int i, j, k;
    for( i = 0 ; i < N ; i++ )
    {
        if( mmst[x][i] && i != p )
        {
            dfs(i, x);
        }
    }
    if( p != -1 && p != N - 1 )
    {
        for( i = 0 ; i < N - 1 ; i++ )
        {
            for( j = 0 ; j < N - 1 && aa[i][x][j][0] != -1 ; j++ )
            {
                for( k = 0 ; k < M ; k++ )
                {
                    if( aa[i][p][k][0] == -1 || aa[i][p][k][0] == aa[i][x][j][0] )
                    {
                        aa[i][p][k][0] = aa[i][x][j][0];
                        aa[i][p][k][1] += aa[i][x][j][1];
                        break;
                    }
                }
            }
        }
    }
    return;
}
int main()
{
    int i, j, k, c = 0;
    long long mst, tst, tmst, C, min, **a;
    scanf("%d%d", &N, &M);
    u = (int*)malloc(M * sizeof(int));
    v = (int*)malloc(M * sizeof(int));
    w = (int*)malloc(M * sizeof(int));
    a = (long long**)malloc(N * sizeof(long long*));
    for( i = 0 ; i < N ; i++ )
    {
        a[i] = (long long*)malloc(N * sizeof(long long));
    }
    for( i = 0 ; i < M ; i++ )
    {
        scanf("%d%d%d", u + i, v + i, w + i);
    }
    for( i = 0 ; i < 100 ; i++ )
    {
        map[i] = -1;
    }
    for( i = 0 ; i < M ; i++ )
    {
        if( map[u[i] - 1] == -1 )
        {
            map[u[i] - 1] = ++c;
        }
        if( map[v[i] - 1] == -1 )
        {
            map[v[i] - 1] = ++c;
        }
        u[i] = map[u[i] - 1];
        v[i] = map[v[i] - 1];
    }
    sort_a3(w, u, v, M);
    mst = MST();
    for( i = 0 ; i < N - 1 ; i++ )
    {
        for( j = 0 ; j < N - 1 ; j++ )
        {
            a[i][j] = 0;
        }
    }
    for( i = 0 ; i < M ; i++ )
    {
        if( u[i] != N )
        {
            a[u[i] - 1][u[i] - 1]++;
        }
        if( v[i] != N )
        {
            a[v[i] - 1][v[i] - 1]++;
        }
        if( u[i] != N && v[i] != N )
        {
            a[u[i] - 1][v[i] - 1]--;
            a[v[i] - 1][u[i] - 1]--;
        }
    }
    tst = det(a, N - 1);
    for( i = 0 ; i < N - 1 ; i++ )
    {
        for( j = 0 ; j < N - 1 ; j++ )
        {
            for( k = 0 ; k < M ; k++ )
            {
                aa[i][j][k][0] = -1;
                aa[i][j][k][1] = 0;
            }
        }
    }
    for( i = 0 ; i < M ; i++ )
    {
        if( u[i] != N )
        {
            for( j = 0 ; j < M ; j++ )
            {
                if( aa[u[i] - 1][u[i] - 1][j][0] == -1 || aa[u[i] - 1][u[i] - 1][j][0] == w[i] )
                {
                    aa[u[i] - 1][u[i] - 1][j][0] = w[i];
                    aa[u[i] - 1][u[i] - 1][j][1]++;
                    break;
                }
            }
        }
        if( v[i] != N )
        {
            for( j = 0 ; j < M ; j++ )
            {
                if( aa[v[i] - 1][v[i] - 1][j][0] == -1 || aa[v[i] - 1][v[i] - 1][j][0] == w[i] )
                {
                    aa[v[i] - 1][v[i] - 1][j][0] = w[i];
                    aa[v[i] - 1][v[i] - 1][j][1]++;
                    break;
                }
            }
        }
        if( u[i] != N && v[i] != N )
        {
            for( j = 0 ; j < M ; j++ )
            {
                if( aa[u[i] - 1][v[i] - 1][j][0] == -1 || aa[u[i] - 1][v[i] - 1][j][0] == w[i] )
                {
                    aa[u[i] - 1][v[i] - 1][j][0] = w[i];
                    aa[u[i] - 1][v[i] - 1][j][1]--;
                    break;
                }
            }
            for( j = 0 ; j < M ; j++ )
            {
                if( aa[v[i] - 1][u[i] - 1][j][0] == -1 || aa[v[i] - 1][u[i] - 1][j][0] == w[i] )
                {
                    aa[v[i] - 1][u[i] - 1][j][0] = w[i];
                    aa[v[i] - 1][u[i] - 1][j][1]--;
                    break;
                }
            }
        }
    }
    dfs(N - 1, -1);
    for( j = 0 ; j < N - 1 ; j++ )
    {
        min = -1;
        for( i = 0 ; i < N - 1 ; i++ )
        {
            for( k = 0 ; k < M && aa[i][j][k][0] != -1 ; k++ )
            {
                if( ( min == -1 || aa[i][j][k][0] < min ) && aa[i][j][k][1] )
                {
                    min = aa[i][j][k][0];
                }
            }
        }
        for( i = 0 ; i < N - 1 ; i++ )
        {
            a[i][j] = 0;
            for( k = 0 ; k < M && aa[i][j][k][0] != -1 ; k++ )
            {
                if( aa[i][j][k][0] == min )
                {
                    a[i][j] = aa[i][j][k][1];
                    break;
                }
            }
        }
    }
    tmst = det(a, N - 1);
    C = CC(tst, tmst);
    printf("%lld/%lld", tmst / C, tst / C);
    return 0;
}
