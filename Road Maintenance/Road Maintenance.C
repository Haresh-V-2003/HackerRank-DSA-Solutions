#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _node{
  int x;
  int w;
  struct _node *next;
} lnode;
#define MOD 1000000007
void insert_edge(int x,int y,int w);
void dfs(int x);
int M,trace[100000]={0};
long long dp[6][6][100000]={0};
lnode *table[100000]={0};

int main(){
  int N,x,y,i;
  long long ans;
  scanf("%d%d",&N,&M);
  for(i=0;i<N-1;i++){
    scanf("%d%d",&x,&y);
    insert_edge(x-1,y-1,1);
  }
  dfs(0);
  for(i=ans=0;i<=M;i++)
    ans=(ans+dp[i][M][0])%MOD;
  printf("%lld",ans);
  return 0;
}
void insert_edge(int x,int y,int w){
  lnode *t=malloc(sizeof(lnode));
  t->x=y;
  t->w=w;
  t->next=table[x];
  table[x]=t;
  t=malloc(sizeof(lnode));
  t->x=x;
  t->w=w;
  t->next=table[y];
  table[y]=t;
  return;
}
void dfs(int x){
  int i,j,k,l;
  long long t[6][6];
  lnode *p;
  trace[x]=1;
  dp[0][0][x]=1;
  for(p=table[x];p;p=p->next)
    if(!trace[p->x]){
      dfs(p->x);
      memset(t,0,sizeof(t));
      for(i=0;i<=M;i++)
        for(j=0;i+j<=M+1;j++)
          for(k=0;k<=i;k++)
            for(l=0;l<=j;l++){
              if(i+j<=M){
                t[k][i+j]=(t[k][i+j]+dp[k][i][x]*dp[l][j][p->x])%MOD;
                if(k)
                  t[k-1][i+j]=(t[k-1][i+j]+dp[k][i][x]*dp[l][j][p->x]%MOD*k)%MOD;
                if(k+1<=i+j)
                  t[k+1][i+j]=(t[k+1][i+j]+dp[k][i][x]*dp[l][j][p->x]%MOD*l)%MOD;
              }
              if(i+j && k)
                t[k-1][i+j-1]=(t[k-1][i+j-1]+dp[k][i][x]*dp[l][j][p->x]%MOD*k*l)%MOD;
              if(i+j+1<=M)
                t[k+1][i+j+1]=(t[k+1][i+j+1]+dp[k][i][x]*dp[l][j][p->x])%MOD;
            }
      for(i=0;i<=M;i++)
        for(j=0;j<=M;j++)
          dp[i][j][x]=t[i][j]%MOD;
    }
  return;
}
