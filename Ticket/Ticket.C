#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 510
#define INF 100000000
#define E 0.0001
#define MAX 60000
double cost[N][N], lx[N], ly[N], slack[N], price[100];
int n, max_match, xy[N], yx[N], S[N], T[N], slackx[N], prev[N], d[500], ans[500];
char dd[100][200], ds[200];
int equal(double x, double y)
{
    if( y - x < E && x - y < E )
    {
        return 1;
    }
    return 0;
}
void init_labels()
{
    int x, y;
    for( x = 0 ; x < N ; x++ )
    {
        lx[x] = ly[x] = 0;
    }
    for( x = 0 ; x < n ; x++ )
    {
        for( y = 0 ; y < n ; y++ )
        {
            lx[x] = ( lx[x] > cost[x][y] ) ? lx[x] : cost[x][y];
        }
    }
}
void augment()
{
    if( max_match == n )
    {
        return;
    }
    int x, y, root, q[N], wr = 0, rd = 0;
    memset(S, 0, sizeof(S));
    memset(T, 0, sizeof(T));
    memset(prev, -1, sizeof(prev));
    for( x = 0 ; x < n ; x++ )
    {
        if( xy[x] == -1 )
        {
            q[wr++] = root = x;
            prev[x] = -2;
            S[x] = 1;
            break;
        }
    }
    for( y = 0 ; y < n ; y++ )
    {
        slack[y] = lx[root] + ly[y] - cost[root][y];
        slackx[y] = root;
    }
    while(1)
    {
        while( rd < wr )
        {
            x = q[rd++];
            for( y = 0 ; y < n ; y++ )
            {
                if( equal(cost[x][y] , lx[x] + ly[y]) &&  !T[y] )
                {
                    if( yx[y] == -1 )
                    {
                        break;
                    }
                    T[y] = 1;
                    q[wr++] = yx[y];
                    add_to_tree(yx[y], x);
                }
            }
            if( y < n )
            {
                break;
            }
        }
        if( y < n )
        {
            break;
        }
        update_labels();
        wr = rd = 0;                
        for( y = 0 ; y < n ; y++ )
        {
            if( !T[y] &&  equal(slack[y] , 0) )
            {
                if( yx[y] == -1 )
                {
                    x = slackx[y];
                    break;
                }
                else
                {
                    T[y] = 1;
                    if(!S[yx[y]])    
                    {
                        q[wr++] = yx[y];
                        add_to_tree(yx[y], slackx[y]);
                    }
                }
            }
        }
        if( y < n )
        {
            break;
        }
    }
    if( y < n )
    {
        int cx, cy, ty;
        max_match++;
        for( cx = x, cy = y ; cx != -2 ; cx = prev[cx], cy = ty )
        {
            ty = xy[cx];
            yx[cy] = cx;
            xy[cx] = cy;
        }
        augment();
    }
}
void update_labels()
{
    int x, y;
    double delta = INF;
    for( y = 0 ; y < n ; y++ )
    {
        if(!T[y])
        {
            delta = ( delta < slack[y] ) ? delta : slack[y];
        }
    }
    for( x = 0 ; x < n ; x++ )
    {
        if(S[x])
        {
            lx[x] -= delta;
        }
    }
    for( y = 0 ; y < n ; y++ )
    {
        if(T[y])
        {
            ly[y] += delta;
        }
    }
    for( y = 0 ; y < n ; y++ )
    {
        if(!T[y])
        {
            slack[y] -= delta;
        }
    }
}
void add_to_tree(int x, int prevx) 
{
    int y;
    S[x] = 1;
    prev[x] = prevx;
    for( y = 0 ; y < n ; y++ )
    {
        if( lx[x] + ly[y] - cost[x][y] < slack[y] )
        {
            slack[y] = lx[x] + ly[y] - cost[x][y];
            slackx[y] = x;
        }
    }
}
double hungarian()
{
    double ret = 0;
    max_match = 0;
    memset(xy, -1, sizeof(xy));
    memset(yx, -1, sizeof(yx));
    init_labels();
    augment();
    int x;
    for( x = 0 ; x < n ; x++ )
    {
        ret += cost[x][xy[x]];
    }
    return ret;
}
int main()
{
    double a = 0;
    int nn, m, k, i, j, t;
    scanf("%d%d%d", &nn, &m, &k);
    for( i = 0 ; i < k ; i++ )
    {
        scanf("%s%lf", &dd[i][0], price+i);
    }
    for( i = 0 ; i < nn ; i++ )
    {
        scanf("%s", ds);
        for( j = 0 ; j < k ; j++ )
        {
            if( strcmp(ds, &dd[j][0]) == 0 )
            {
                d[i] = j;
                break;
            }
        }
    }
    n = nn + m;
    for( i = 0 ; i < n ; i++ )
    {
        for( j = 0 ; j < n ; j++ )
        {
            if( j < m || j <= i )
            {
                cost[i][j] = 0;
            }
            else if( i < m || d[i-m] != d[j-m] )
            {
                cost[i][j] = MAX - price[d[j-m]];
            }
            else
            {
                cost[i][j] = MAX - price[d[j-m]] * 0.8;
            }
        }
    }
    a = hungarian();
    for( i = 0 ; i < m ; i++ )
    {
        if(equal(cost[i][xy[i]], 0))
        {
            continue;
        }
        t = xy[i];
        while(1)
        {
            ans[t-m] = i + 1;
            if(equal(cost[t][xy[t]], 0))
            {
                break;
            }
            t = xy[t];
        }
    }
    printf("%.3lf\n", MAX * (double)nn - a);
    for( i = 0 ; i <nn ; i++ )
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}
