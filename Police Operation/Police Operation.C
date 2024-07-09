#include <stdio.h>
#include <stdlib.h>
int get_i(double *a,int num,int size);
double med(double *a,int size);
double inter(long long m1,long long n1,long long m2,long long n2);
int a[2000000];
long long dp[2000000],m[2000000],n[2000000];
double aa[2000000];

int main(){
  int N,h,aa_size=0,i,j;
  long long t,tt;
  scanf("%d%d",&N,&h);
  for(i=0;i<N;i++)
    scanf("%d",a+i);
  for(i=0;i<N;i++){
    if(i)
      dp[i]=h+dp[i-1];
    else
      dp[i]=h;
    if(i && a[i]==a[i-1]){
      dp[i]=dp[i-1];
      continue;
    }
    if(aa_size){
      j=get_i(aa,a[i],aa_size-1);
      t=a[i]*(long long)a[i]+m[j]*a[i]+n[j];
      if(t<dp[i])
        dp[i]=t;
    }
    m[aa_size]=-2*a[i];
    if(i)
      n[aa_size]=a[i]*(long long)a[i]+h+dp[i-1];
    else
      n[aa_size]=a[i]*(long long)a[i]+h;
    j=++aa_size;
    while(aa_size>2){
      if(inter(m[aa_size-3],n[aa_size-3],m[j-1],n[j-1])>aa[aa_size-3])
        break;
      aa_size--;
    }
    tt=m[j-1];
    m[j-1]=m[aa_size-1];
    m[aa_size-1]=tt;
    tt=n[j-1];
    n[j-1]=n[aa_size-1];
    n[aa_size-1]=tt;
    if(aa_size>1)
      aa[aa_size-2]=inter(m[aa_size-2],n[aa_size-2],m[aa_size-1],n[aa_size-1]);
  }
  printf("%lld",dp[N-1]);
  return 0;
}
int get_i(double *a,int num,int size){
  if(size==0)
    return 0;
  if(num>med(a,size))
    return get_i(&a[(size+1)>>1],num,size>>1)+((size+1)>>1);
  else
    return get_i(a,num,(size-1)>>1);
}
double med(double *a,int size){
  return a[(size-1)>>1];
}
double inter(long long m1,long long n1,long long m2,long long n2){
  return (n2-n1)/(double)(m1-m2);
}
