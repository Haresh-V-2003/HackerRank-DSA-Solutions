#include<stdio.h>
#include<stdlib.h>
#define CLOCK   1000000007
#define MODINV4 250000002
long int c[10000], M[10001][101];
long int fast_exp(long int x, int n, int clock)
{
    if( n == 0 )
    {
        return 1;
    }
    long int y = 1;
    while( n > 1 )
    {
        if( n % 2 == 0 )
        {
            x = x * x % clock;
            n = n / 2;
        }
        else
        {
            y = x * y % clock;
            x = x * x % clock;
            n = ( n - 1 ) / 2;
        }
    }
    return x * y % clock;
}
void compute_combinations(int n, int *army)
{
    int vals[4] = { 2, 2, 0, -4 };
    for( int i = 0 ; i < n ; i++ )
    {
        int div = army[i] / 4;
        int rem = army[i] % 4;
        if( div % 2 == 0 )
        {
            c[i] = fast_exp(2, army[i], CLOCK) + fast_exp(4, div, CLOCK) * ( vals[rem] + CLOCK );
        }
        else
        {
            c[i] = fast_exp(2, army[i], CLOCK) - fast_exp(4, div, CLOCK) * ( vals[rem] - CLOCK );
        }
        c[i] %= CLOCK;
        c[i] = c[i] * MODINV4 % CLOCK;
    }
}
int king(int n, int k, int* army)
{
    compute_combinations(n, army);
    for( int i = 0 ; i <= n ; i++ )
    {
        M[i][0] = 1;
    }
    for( int i = 1 ; i <= n ; i++ )
    {
        for( int j = 1 ; j <= k ; j++ )
        {
            M[i][j] = c[i - 1] * M[i - 1][j - 1] + M[i - 1][j];
            M[i][j] %= CLOCK;
        }
    }
    return M[n][k];
}
int main()
{
    FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");
    int n, k;
    scanf("%d %d", &n, &k);
    int *army = malloc(n * sizeof(int));
    for( int i = 0 ; i < n ; i++ )
    {
        scanf("%d", &army[i]);
    }
    fprintf(fptr, "%d\n", king(n, k, army));
    fclose(fptr);
    return 0;
}
