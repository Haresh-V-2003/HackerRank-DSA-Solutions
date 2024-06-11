#include <stdio.h>
#include <stdlib.h>
#define MOD1 1000000007
#define MOD2 1000000009
#define HASH_SIZE 123455
typedef struct _node{
  int x;
  int y;
  struct _node *next;
} node;
void solve(int i,int j);
void insert(int x,int y);
void freehash();
long long modInverse(long long a,long long mod);
char a[2][601];
int hash_count,N;
long long tr1[1200],tl1[1200],br1[1200],bl1[1200],dr1[1200],dl1[1200],ur1[1200],ul1[1200],mod1[1201],inmod1[1201];
long long tr2[1200],tl2[1200],br2[1200],bl2[1200],dr2[1200],dl2[1200],ur2[1200],ul2[1200],mod2[1201],inmod2[1201];
node *hash[HASH_SIZE]={0};

int main(){
  int T,i,j;
  long long t1,t2;
  scanf("%d",&T);
  while(T--){
    hash_count=0;
    scanf("%d%s%s",&N,&a[0][0],&a[1][0]);
    for(i=0,t1=t2=1;i<N;i++,t1=t1*26%MOD1,t2=t2*26%MOD2)
      if(i){
        tl1[i]=((a[0][i]-'a')*t1+tl1[i-1])%MOD1;
        bl1[i]=((a[1][i]-'a')*t1+bl1[i-1])%MOD1;
        tl2[i]=((a[0][i]-'a')*t2+tl2[i-1])%MOD2;
        bl2[i]=((a[1][i]-'a')*t2+bl2[i-1])%MOD2;
      }
      else{
        tl1[i]=a[0][i]-'a';
        bl1[i]=a[1][i]-'a';
        tl2[i]=a[0][i]-'a';
        bl2[i]=a[1][i]-'a';
      }
    for(i=N-1;i>=0;i--,t1=t1*26%MOD1,t2=t2*26%MOD2){
      tl1[2*N-i-1]=((a[1][i]-'a')*t1+tl1[2*N-i-2])%MOD1;
      bl1[2*N-i-1]=((a[0][i]-'a')*t1+bl1[2*N-i-2])%MOD1;
      tl2[2*N-i-1]=((a[1][i]-'a')*t2+tl2[2*N-i-2])%MOD2;
      bl2[2*N-i-1]=((a[0][i]-'a')*t2+bl2[2*N-i-2])%MOD2;
    }
    for(i=N-1,t1=t2=1;i>=0;i--,t1=t1*26%MOD1,t2=t2*26%MOD2)
      if(i!=N-1){
        tr1[N-i-1]=((a[0][i]-'a')*t1+tr1[N-i-2])%MOD1;
        br1[N-i-1]=((a[1][i]-'a')*t1+br1[N-i-2])%MOD1;
        tr2[N-i-1]=((a[0][i]-'a')*t2+tr2[N-i-2])%MOD2;
        br2[N-i-1]=((a[1][i]-'a')*t2+br2[N-i-2])%MOD2;
      }
      else{
        tr1[N-i-1]=a[0][i]-'a';
        br1[N-i-1]=a[1][i]-'a';
        tr2[N-i-1]=a[0][i]-'a';
        br2[N-i-1]=a[1][i]-'a';
      }
    for(i=0;i<N;i++,t1=t1*26%MOD1,t2=t2*26%MOD2){
      tr1[i+N]=((a[1][i]-'a')*t1+tr1[i+N-1])%MOD1;
      br1[i+N]=((a[0][i]-'a')*t1+br1[i+N-1])%MOD1;
      tr2[i+N]=((a[1][i]-'a')*t2+tr2[i+N-1])%MOD2;
      br2[i+N]=((a[0][i]-'a')*t2+br2[i+N-1])%MOD2;
    }
    for(i=0,t1=t2=1;i<N;i++){
      if(i%2){
        ul1[2*i]=((a[0][i]-'a')*t1+ul1[2*i-1])%MOD1;
        dl1[2*i]=((a[1][i]-'a')*t1+dl1[2*i-1])%MOD1;
        ul2[2*i]=((a[0][i]-'a')*t2+ul2[2*i-1])%MOD2;
        dl2[2*i]=((a[1][i]-'a')*t2+dl2[2*i-1])%MOD2;
      }
      else
        if(!i){
          ul1[2*i]=a[1][i]-'a';
          dl1[2*i]=a[0][i]-'a';
          ul2[2*i]=a[1][i]-'a';
          dl2[2*i]=a[0][i]-'a';
        }
        else{
          ul1[2*i]=((a[1][i]-'a')*t1+ul1[2*i-1])%MOD1;
          dl1[2*i]=((a[0][i]-'a')*t1+dl1[2*i-1])%MOD1;
          ul2[2*i]=((a[1][i]-'a')*t2+ul2[2*i-1])%MOD2;
          dl2[2*i]=((a[0][i]-'a')*t2+dl2[2*i-1])%MOD2;
        }
      t1=t1*26%MOD1;
      t2=t2*26%MOD2;
      if(i%2){
        ul1[2*i+1]=((a[1][i]-'a')*t1+ul1[2*i])%MOD1;
        dl1[2*i+1]=((a[0][i]-'a')*t1+dl1[2*i])%MOD1;
        ul2[2*i+1]=((a[1][i]-'a')*t2+ul2[2*i])%MOD2;
        dl2[2*i+1]=((a[0][i]-'a')*t2+dl2[2*i])%MOD2;
      }
      else{
        ul1[2*i+1]=((a[0][i]-'a')*t1+ul1[2*i])%MOD1;
        dl1[2*i+1]=((a[1][i]-'a')*t1+dl1[2*i])%MOD1;
        ul2[2*i+1]=((a[0][i]-'a')*t2+ul2[2*i])%MOD2;
        dl2[2*i+1]=((a[1][i]-'a')*t2+dl2[2*i])%MOD2;
      }
      t1=t1*26%MOD1;
      t2=t2*26%MOD2;
    }
    for(i=N-1,t1=t2=1;i>=0;i--)
      if(i==N-1){
        ur1[2*(N-1-i)]=a[1][i]-'a';
        dr1[2*(N-1-i)]=a[0][i]-'a';
        ur2[2*(N-1-i)]=a[1][i]-'a';
        dr2[2*(N-1-i)]=a[0][i]-'a';
        t1=t1*26%MOD1;
        t2=t2*26%MOD2;
        ur1[2*(N-1-i)+1]=((a[0][i]-'a')*t1+ur1[2*(N-1-i)])%MOD1;
        dr1[2*(N-1-i)+1]=((a[1][i]-'a')*t1+dr1[2*(N-1-i)])%MOD1;
        ur2[2*(N-1-i)+1]=((a[0][i]-'a')*t2+ur2[2*(N-1-i)])%MOD2;
        dr2[2*(N-1-i)+1]=((a[1][i]-'a')*t2+dr2[2*(N-1-i)])%MOD2;
        t1=t1*26%MOD1;
        t2=t2*26%MOD2;
      }
      else{
        if((N-i)%2==0){
          ur1[2*(N-1-i)]=((a[0][i]-'a')*t1+ur1[2*(N-1-i)-1])%MOD1;
          dr1[2*(N-1-i)]=((a[1][i]-'a')*t1+dr1[2*(N-1-i)-1])%MOD1;
          ur2[2*(N-1-i)]=((a[0][i]-'a')*t2+ur2[2*(N-1-i)-1])%MOD2;
          dr2[2*(N-1-i)]=((a[1][i]-'a')*t2+dr2[2*(N-1-i)-1])%MOD2;
        }
        else{
          ur1[2*(N-1-i)]=((a[1][i]-'a')*t1+ur1[2*(N-1-i)-1])%MOD1;
          dr1[2*(N-1-i)]=((a[0][i]-'a')*t1+dr1[2*(N-1-i)-1])%MOD1;
          ur2[2*(N-1-i)]=((a[1][i]-'a')*t2+ur2[2*(N-1-i)-1])%MOD2;
          dr2[2*(N-1-i)]=((a[0][i]-'a')*t2+dr2[2*(N-1-i)-1])%MOD2;
        }
        t1=t1*26%MOD1;
        t2=t2*26%MOD2;
        if((N-i)%2==0){
          ur1[2*(N-1-i)+1]=((a[1][i]-'a')*t1+ur1[2*(N-1-i)])%MOD1;
          dr1[2*(N-1-i)+1]=((a[0][i]-'a')*t1+dr1[2*(N-1-i)])%MOD1;
          ur2[2*(N-1-i)+1]=((a[1][i]-'a')*t2+ur2[2*(N-1-i)])%MOD2;
          dr2[2*(N-1-i)+1]=((a[0][i]-'a')*t2+dr2[2*(N-1-i)])%MOD2;
        }
        else{
          ur1[2*(N-1-i)+1]=((a[0][i]-'a')*t1+ur1[2*(N-1-i)])%MOD1;
          dr1[2*(N-1-i)+1]=((a[1][i]-'a')*t1+dr1[2*(N-1-i)])%MOD1;
          ur2[2*(N-1-i)+1]=((a[0][i]-'a')*t2+ur2[2*(N-1-i)])%MOD2;
          dr2[2*(N-1-i)+1]=((a[1][i]-'a')*t2+dr2[2*(N-1-i)])%MOD2;
        }
        t1=t1*26%MOD1;
        t2=t2*26%MOD2;
      }
    for(i=0;i<=2*N;i++)
      if(i){
        mod1[i]=mod1[i-1]*26%MOD1;
        inmod1[i]=modInverse(mod1[i],MOD1);
        mod2[i]=mod2[i-1]*26%MOD2;
        inmod2[i]=modInverse(mod2[i],MOD2);
      }
      else
        mod1[i]=inmod1[i]=mod2[i]=inmod2[i]=1;
    for(i=0;i<=N;i++)
      for(j=i;j<=N;j++)
        solve(i,j);
    printf("%d\n",hash_count);
    freehash();
  }
  return 0;
}
void solve(int i,int j){
  long long t1,t2,t3,t4,t5,t6,t7,t8,t9;
  long long tt1,tt2,tt3,tt4,tt5,tt6,tt7,tt8,tt9;
  t1=tr1[N+i-1];
  t2=br1[N+i-1];
  if(i!=N){
    t1=(t1-tr1[N-i-1]+MOD1)%MOD1;
    t2=(t2-br1[N-i-1]+MOD1)%MOD1;
  }
  t1=t1*inmod1[N-i]%MOD1;
  t2=t2*inmod1[N-i]%MOD1;
  t3=tl1[2*N-j-1];
  t4=bl1[2*N-j-1];
  if(j){
    t3=(t3-tl1[j-1]+MOD1)%MOD1;
    t4=(t4-bl1[j-1]+MOD1)%MOD1;
  }
  t3=t3*inmod1[j]%MOD1;
  t4=t4*inmod1[j]%MOD1;
  if(!j)
    t5=t6=0;
  else{
    t5=ul1[2*j-1];
    t6=dl1[2*j-1];
    if(i){
      t5=(t5-ul1[2*i-1]+MOD1)%MOD1;
      t6=(t6-dl1[2*i-1]+MOD1)%MOD1;
    }
  }
  if(i==N)
    t7=t8=0;
  else{
    t7=ur1[2*(N-i)-1];
    t8=dr1[2*(N-i)-1];
    if(j!=N){
      t7=(t7-ur1[2*(N-j)-1]+MOD1)%MOD1;
      t8=(t8-dr1[2*(N-j)-1]+MOD1)%MOD1;
    }
  }
  tt1=tr2[N+i-1];
  tt2=br2[N+i-1];
  if(i!=N){
    tt1=(tt1-tr2[N-i-1]+MOD2)%MOD2;
    tt2=(tt2-br2[N-i-1]+MOD2)%MOD2;
  }
  tt1=tt1*inmod2[N-i]%MOD2;
  tt2=tt2*inmod2[N-i]%MOD2;
  tt3=tl2[2*N-j-1];
  tt4=bl2[2*N-j-1];
  if(j){
    tt3=(tt3-tl2[j-1]+MOD2)%MOD2;
    tt4=(tt4-bl2[j-1]+MOD2)%MOD2;
  }
  tt3=tt3*inmod2[j]%MOD2;
  tt4=tt4*inmod2[j]%MOD2;
  if(!j)
    tt5=tt6=0;
  else{
    tt5=ul2[2*j-1];
    tt6=dl2[2*j-1];
    if(i){
      tt5=(tt5-ul2[2*i-1]+MOD2)%MOD2;
      tt6=(tt6-dl2[2*i-1]+MOD2)%MOD2;
    }
  }
  if(i==N)
    tt7=tt8=0;
  else{
    tt7=ur2[2*(N-i)-1];
    tt8=dr2[2*(N-i)-1];
    if(j!=N){
      tt7=(tt7-ur2[2*(N-j)-1]+MOD2)%MOD2;
      tt8=(tt8-dr2[2*(N-j)-1]+MOD2)%MOD2;
    }
  }
  t9=t1;
  if(i%2)
    t9+=t6;
  else
    t9+=t5;
  if((j-i)%2)
    t9+=t3*mod1[j*2]%MOD1;
  else
    t9+=t4*mod1[j*2]%MOD1;
  t9%=MOD1;
  tt9=tt1;
  if(i%2)
    tt9+=tt6;
  else
    tt9+=tt5;
  if((j-i)%2)
    tt9+=tt3*mod2[j*2]%MOD2;
  else
    tt9+=tt4*mod2[j*2]%MOD2;
  tt9%=MOD2;
  insert(t9,tt9);
  t9=t2;
  if(i%2)
    t9+=t5;
  else
    t9+=t6;
  if((j-i)%2)
    t9+=t4*mod1[j*2]%MOD1;
  else
    t9+=t3*mod1[j*2]%MOD1;
  t9%=MOD1;
  tt9=tt2;
  if(i%2)
    tt9+=tt5;
  else
    tt9+=tt6;
  if((j-i)%2)
    tt9+=tt4*mod2[j*2]%MOD2;
  else
    tt9+=tt3*mod2[j*2]%MOD2;
  tt9%=MOD2;
  insert(t9,tt9);
  t9=t3;
  if((N-j)%2)
    t9+=t8;
  else
    t9+=t7;
  if((j-i)%2)
    t9+=t1*mod1[(N-i)*2]%MOD1;
  else
    t9+=t2*mod1[(N-i)*2]%MOD1;
  t9%=MOD1;
  tt9=tt3;
  if((N-j)%2)
    tt9+=tt8;
  else
    tt9+=tt7;
  if((j-i)%2)
    tt9+=tt1*mod2[(N-i)*2]%MOD2;
  else
    tt9+=tt2*mod2[(N-i)*2]%MOD2;
  tt9%=MOD2;
  insert(t9,tt9);
  t9=t4;
  if((N-j)%2)
    t9+=t7;
  else
    t9+=t8;
  if((j-i)%2)
    t9+=t2*mod1[(N-i)*2]%MOD1;
  else
    t9+=t1*mod1[(N-i)*2]%MOD1;
  t9%=MOD1;
  tt9=tt4;
  if((N-j)%2)
    tt9+=tt7;
  else
    tt9+=tt8;
  if((j-i)%2)
    tt9+=tt2*mod2[(N-i)*2]%MOD2;
  else
    tt9+=tt1*mod2[(N-i)*2]%MOD2;
  tt9%=MOD2;
  insert(t9,tt9);
  return;
}
void insert(int x,int y){
  int bucket=(x+y)%HASH_SIZE;
  node *t=hash[bucket];
  while(t){
    if(t->x==x && t->y==y)
      return;
    t=t->next;
  }
  t=(node*)malloc(sizeof(node));
  t->x=x;
  t->y=y;
  t->next=hash[bucket];
  hash[bucket]=t;
  hash_count++;
  return;
}
void freehash(){
  int i;
  node *t,*p;
  for(i=0;i<HASH_SIZE;i++){
    t=hash[i];
    while(t){
      p=t->next;
      free(t);
      t=p;
    }
    hash[i]=NULL;
  }
  return;
}
long long modInverse(long long a,long long mod){
    long long b0 = mod, t, q;
    long long x0 = 0, x1 = 1;
    while (a > 1) {
        q = a / mod;
        t = mod; mod = a % mod; a = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}
