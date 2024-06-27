#include <assert.h>
#include <limits.h>
#include <linux/limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int num, num1, i, ss, dd, h, lq, eng, vertical[2100000], path[2100000];
int  V[2100000], few[2100000];
int hum[2100000];
long long dig[2100000];
int land[2100000];
bool snow[2100000], sand[2100000];
void sol(int a, int b, int c, int d) 
{
  path[++eng] = vertical[a];
  vertical[a] = eng;
  V[eng] = b;
  land[eng] = c;
  hum[eng] = d;
}

bool dfs(int x) 
{
  sand[x] = true;
  for (int i = vertical[x]; i; i = path[i])
    if (land[i]) {
      if (dig[x] + hum[i] < dig[V[i]])
      {
        dig[V[i]] = dig[x] + hum[i];
        few[V[i]] = i;
        if (!sand[V[i]]) 
        {
          if (dfs(V[i]))
            return true;
        } else 
        {
          lq = V[i];
          return true;
        }
      }
    }
  sand[x] = false;
  return false;
}

int fi()
{
    int i;
    for (i = 1; i <= num; i++)
      snow[i] = false, dig[i] = 0, sand[i] = false;
    for (i = 1; i <= num; i++)
      if (!snow[i] && dfs(i))
        return i;
    return 0;
}

int main() 
{
    int T;
    scanf("%d", &T);
    while (T--) {
      scanf("%d%d", &num, &num1);
      eng = 1;
      for (int i = 1; i <= num; i++)
        vertical[i] = 0;
      for (int i = 1; i < num; i++) 
      {
        scanf("%d%d%d", &ss, &dd, &h);
        sol(ss, dd, h, 0);
        sol(dd, ss, h, 0);
      }
        long long ans = 0;
        for (int i = 1; i <= num1; i++) 
        {
          scanf("%d%d%d", &ss, &dd, &h);
          sol(dd, ss, 1, -h);
          sol(ss, dd, 0, h);
        }
        while (fi()) 
        {
          for (int i = few[lq];; i = few[V[i ^ 1]]) 
          {
            ans -= hum[i];
            land[i] -= 1;
            land[i ^ 1] += 1;
            if (V[i ^ 1] == lq)
              break;
          }
        }
        printf("%lld\n", ans);
    }
}
