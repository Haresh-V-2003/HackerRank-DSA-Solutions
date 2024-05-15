#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LIM 32100
#define NUM 123456
typedef struct _node{
int x;
int id;
struct _node *next;
} node;
typedef struct _list_node{
int x;
struct _list_node *next;
} list_node;
typedef struct _list{
int size;
list_node *head;
} list;
node **hash;
int *p,hash_size=0,*A,*B,*ALength,**AD,*BLength,**BD,*MA,*MB,*VA,*VB;
int match(int u,int vi);
void getp(long long N,int *prim);
int findid(int x,int iflag);
void freehash();
void insert(list *l,int x);
void freelist(list *l);

int main(){
p=(int*)malloc(LIM*sizeof(int));
hash=(node**)malloc(NUM*sizeof(node*));
memset(hash,0,NUM*sizeof(node*));
getp(LIM,p);
int i,j,ans=0,n,t;
scanf("%d",&n);
A=(int*)malloc(n*sizeof(int));
B=(int*)malloc(n*sizeof(int));
int *Alist=(int*)malloc(13*sizeof(int));
ALength=(int*)malloc(n*sizeof(int));
AD=(int**)malloc(n*sizeof(int*));
list_node *temp;
for(i=0;i<n;i++)
scanf("%d",A+i);
for(i=0;i<n;i++)
scanf("%d",B+i);
for(i=0;i<n;i++){
Alist[0]=0;
for(j=0;p[j]*p[j]<=A[i];j++)
if(A[i]%p[j]==0){
Alist[++Alist[0]]=findid(p[j],1);
while(A[i]%p[j]==0)
A[i]/=p[j];
}
if(A[i]!=1)
Alist[++Alist[0]]=findid(A[i],1);
ALength[i]=Alist[0];
AD[i]=(int*)malloc(Alist[0]*sizeof(int));
for(j=0;j<Alist[0];j++)
AD[i][j]=Alist[Alist[0]-j];
}
free(A);
free(Alist);
list *Blist=(list*)malloc(hash_size*sizeof(list));
BLength=(int*)malloc(hash_size*sizeof(int));
BD=(int**)malloc(hash_size*sizeof(int*));
memset(Blist,0,hash_size*sizeof(list));
for(i=0;i<n;i++){
for(j=0;p[j]*p[j]<=B[i];j++)
if(B[i]%p[j]==0){
t=findid(p[j],0);
if(t!=-1)
insert(Blist+t,i);
while(B[i]%p[j]==0)
B[i]/=p[j];
}
if(B[i]!=1){
t=findid(B[i],0);
if(t!=-1)
insert(Blist+t,i);
}
}
for(i=0;i<hash_size;i++){
BD[i]=(int*)malloc(Blist[i].size*sizeof(int));
BLength[i]=Blist[i].size;
j=Blist[i].size-1;
temp=Blist[i].head;
while(temp){
BD[i][j]=temp->x;
temp=temp->next;
j--;
}
freelist(Blist+i);
}
free(B);
free(Blist);
free(p);
freehash();
MA=(int*)malloc(n*sizeof(int));
MB=(int*)malloc(n*sizeof(int));
VA=(int*)malloc(n*sizeof(int));
VB=(int*)malloc(hash_size*sizeof(int));
memset(MA,-1,n*sizeof(int));
memset(MB,-1,n*sizeof(int));
memset(VA,-1,n*sizeof(int));
memset(VB,-1,hash_size*sizeof(int));
for(i=0;i<n;i++)
if(match(i,i))
ans++;
printf("%d",ans);
return 0;
}
int match(int u,int vi){
int i,j,v;
if(VA[u]==vi)
return 0;
VA[u]=vi;
int *FA=AD[u];
for(i=0;i<ALength[u];i++){
if(VB[FA[i]]==vi)
continue;
for(j=0;j<BLength[FA[i]];j++){
v=BD[FA[i]][j];
if(MB[v]==-1){
MA[u]=v;
MB[v]=u;
return 1;
}
}
}
for(i=0;i<ALength[u];i++){
if(VB[FA[i]]==vi)
continue;
VB[FA[i]]=vi;
for(j=0;j<BLength[FA[i]];j++){
v=BD[FA[i]][j];
if(MA[u]!=v && match(MB[v],vi)){
MA[u]=v;
MB[v]=u;
return 1;
}
}
}
return 0;
}
void getp(long long N,int *prim){
long long i,j,index=2,flag;
prim[0]=2;
prim[1]=3;
for(i=5;i<=N;i=i+2)
{
for(j=1,flag=1;prim[j]<=sqrt(i);j++)
{
if(i%prim[j]==0){
flag=0;
break;}
}
if(flag==1)
{prim[index]=i;
index++;}
}
prim[index]=0;
return;
}
int findid(int x,int iflag){
int b=x%NUM;
node *t=hash[b];
while(t){
if(t->x==x)
return t->id;
t=t->next;
}
if(iflag){
t=(node*)malloc(sizeof(node));
t->x=x;
t->id=hash_size++;
t->next=hash[b];
hash[b]=t;
return t->id;
}
return -1;
}
void freehash(){
int i;
node *t,*p;
for(i=0;i<NUM;i++){
t=hash[i];
while(t){
p=t->next;
free(t);
t=p;
}
}
free(hash);
return;
}
void insert(list *l,int x){
list_node *t=(list_node*)malloc(sizeof(list_node));
t->x=x;
t->next=l->head;
l->head=t;
l->size++;
return;
}
void freelist(list *l){
list_node *t,*p;
t=l->head;
while(t){
p=t->next;
free(t);
t=p;}return;}
