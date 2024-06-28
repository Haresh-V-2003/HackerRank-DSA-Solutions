#include <stdio.h>
#include <stdlib.h>
typedef struct{
  int u;
  long long w;
} node;
void sort_a(long long*a,int size);
void merge(long long*a,long long*left_a,long long*right_a,int left_size,int right_size);
void sort_a2(int*a,int*b,int size);
void merge2(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int left_size,int right_size);
void sort_a3(int*a,int*b,int*c,int size);
void merge3(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int*c,int*left_c,int*right_c,int left_size,int right_size);
void heap_insert(node *heap,node *elem,int *size,int *heap_list);
void heap_update(node *heap,node *elem,int *heap_list);
void heap_read(node *heap,int *size,int *heap_list,node *ans);
int get_i(long long*a,long long num,int size);
long long med(long long*a,int size);
void range_increment(int i,int j,long long val,long long*tree,int N);
long long query(int i,long long*tree,int N);
void DJ(int N,int M,int*u,int*v,int*w,int*v_right,int*list_index,int*left_index,int*right_index,int S,long long*d,int*bridge,int*island);

int main(){
  int N,M,S,D,Q,x,y,p,f,b,i,j;
  int *u,*v,*w,*v_right,*list_index,*left_index,*right_index,*bridge,*island;
  long long *d_s,*d_d,*path,*bypass;
  scanf("%d%d",&N,&M);
  u=(int*)malloc(M*sizeof(int));
  v=(int*)malloc(M*sizeof(int));
  w=(int*)malloc(M*sizeof(int));
  v_right=(int*)malloc(M*sizeof(int));
  list_index=(int*)malloc(M*sizeof(int));
  left_index=(int*)malloc(M*sizeof(int));
  right_index=(int*)malloc(M*sizeof(int));
  d_s=(long long*)malloc(N*sizeof(long long));
  d_d=(long long*)malloc(N*sizeof(long long));
  bridge=(int*)malloc(M*sizeof(int));
  path=(long long*)malloc(M*sizeof(long long));
  island=(int*)malloc(N*sizeof(int));
  bypass=(long long*)malloc(M*3*sizeof(long long));
  for(i=0;i<M;i++){
    scanf("%d%d%d",u+i,v+i,w+i);
    list_index[i]=i;
    bridge[i]=0;
  }
  for(i=0;i<N;i++)
    d_s[i]=d_d[i]=-1;
  for(i=0;i<M*3;i++)
    bypass[i]=-1;
  sort_a3(u,v,w,M);
  for(i=0;i<M;i++)
    v_right[i]=v[i];
  sort_a2(v_right,list_index,M);
  for(i=0;i<M;i++){
    if(i==0 || u[i]!=u[i-1])
      left_index[u[i]]=i;
    if(i==0 || v_right[i]!=v_right[i-1])
      right_index[v_right[i]]=i;
  }
  scanf("%d%d%d",&S,&D,&Q);
  f=0;
  DJ(N,M,u,v,w,v_right,list_index,left_index,right_index,S,d_s,bridge,island);
  DJ(N,M,u,v,w,v_right,list_index,left_index,right_index,D,d_d,bridge,island);
  if(d_s[D]==-1)
    f=1;
  else{
    for(i=0,p=0;i<M;i++)
      if(d_s[u[i]]!=-1 && (d_s[u[i]]+d_d[v[i]]+w[i]==d_s[D] || d_s[v[i]]+d_d[u[i]]+w[i]==d_s[D])){
        bridge[i]=1;
        path[p]=(d_s[u[i]]>d_s[v[i]])?d_s[u[i]]:d_s[v[i]];
        p++;
      }
    sort_a(path,p);
    for(i=0,b=0;i<M;i++)
      if(bridge[i]){
        x=(d_s[u[i]]<d_s[v[i]])?d_s[u[i]]:d_s[v[i]];
        y=(d_s[u[i]]<d_s[v[i]])?d_s[v[i]]:d_s[u[i]];
        j=get_i(path,x,p);
        if(path[j]==y && (j==p-1 || path[j+1]>y)){
          bridge[i]=2;
          b++;
        }
      }
    for(i=0;i<N;i++)
      d_s[i]=island[i]=-1;
    DJ(N,M,u,v,w,v_right,list_index,left_index,right_index,S,d_s,bridge,island);
    for(i=0;i<M;i++)
      if(bridge[i]!=2){
        x=(island[u[i]]>island[v[i]])?island[v[i]]:island[u[i]];
        y=(island[u[i]]>island[v[i]])?island[u[i]]:island[v[i]];
        j=(island[u[i]]>island[v[i]])?d_s[v[i]]+w[i]+d_d[u[i]]:d_s[u[i]]+w[i]+d_d[v[i]];
        range_increment(x+1,y,j,bypass,b);
      }
  }
  while(Q--){
    scanf("%d%d",&x,&y);
    if(f)
      printf("Infinity\n");
    else{
      for(i=left_index[x];i>=0 && i<M && u[i]==x;i++)
        if(v[i]==y)
          if(bridge[i]==2)
            if(query((island[u[i]]>island[v[i]])?island[v[i]]+1:island[u[i]]+1,bypass,b)==-1)
              printf("Infinity\n");
            else
              printf("%lld\n",query((island[u[i]]>island[v[i]])?island[v[i]]+1:island[u[i]]+1,bypass,b));
          else
            printf("%lld\n",d_s[D]);
      for(i=right_index[x];i>=0 && i<M && v_right[i]==x;i++)
        if(u[list_index[i]]==y)
          if(bridge[list_index[i]]==2)
            if(query((island[u[list_index[i]]]>island[v[list_index[i]]])?island[v[list_index[i]]]+1:island[u[list_index[i]]]+1,bypass,b)==-1)
              printf("Infinity\n");
            else
              printf("%lld\n",query((island[u[list_index[i]]]>island[v[list_index[i]]])?island[v[list_index[i]]]+1:island[u[list_index[i]]]+1,bypass,b));
          else
            printf("%lld\n",d_s[D]);
    }
  }
  return 0;
}
void sort_a(long long*a,int size){
  if (size < 2)
    return;
  int m = (size+1)/2,i;
  long long *left_a,*right_a;
  left_a=(long long*)malloc(m*sizeof(long long));
  right_a=(long long*)malloc((size-m)*sizeof(long long));
  for(i=0;i<m;i++)
    left_a[i]=a[i];
  for(i=0;i<size-m;i++)
    right_a[i]=a[i+m];
  sort_a(left_a,m);
  sort_a(right_a,size-m);
  merge(a,left_a,right_a,m,size-m);
  free(left_a);
  free(right_a);
  return;
}
void merge(long long*a,long long*left_a,long long*right_a,int left_size,int right_size){
  int i = 0, j = 0;
  while (i < left_size|| j < right_size) {
    if (i == left_size) {
      a[i+j] = right_a[j];
      j++;
    } else if (j == right_size) {
      a[i+j] = left_a[i];
      i++;
    } else if (left_a[i] <= right_a[j]) {
      a[i+j] = left_a[i];
      i++;
    } else {
      a[i+j] = right_a[j];
      j++;
    }
  }
  return;
}
void sort_a2(int*a,int*b,int size){
  if (size < 2)
    return;
  int m = (size+1)/2,i;
  int*left_a,*left_b,*right_a,*right_b;
  left_a=(int*)malloc(m*sizeof(int));
  right_a=(int*)malloc((size-m)*sizeof(int));
  left_b=(int*)malloc(m*sizeof(int));
  right_b=(int*)malloc((size-m)*sizeof(int));
  for(i=0;i<m;i++){
    left_a[i]=a[i];
    left_b[i]=b[i];
  }
  for(i=0;i<size-m;i++){
    right_a[i]=a[i+m];
    right_b[i]=b[i+m];
  }
  sort_a2(left_a,left_b,m);
  sort_a2(right_a,right_b,size-m);
  merge2(a,left_a,right_a,b,left_b,right_b,m,size-m);
  free(left_a);
  free(right_a);
  free(left_b);
  free(right_b);
  return;
}
void merge2(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int left_size,int right_size){
  int i = 0, j = 0;
  while (i < left_size|| j < right_size) {
    if (i == left_size) {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      j++;
    } else if (j == right_size) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      i++;
    } else if (left_a[i] <= right_a[j]) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      i++;
    } else {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      j++;
    }
  }
  return;
}
void sort_a3(int*a,int*b,int*c,int size){
  if (size < 2)
    return;
  int m = (size+1)/2,i;
  int *left_a,*left_b,*left_c,*right_a,*right_b,*right_c;
  left_a=(int*)malloc(m*sizeof(int));
  right_a=(int*)malloc((size-m)*sizeof(int));
  left_b=(int*)malloc(m*sizeof(int));
  right_b=(int*)malloc((size-m)*sizeof(int));
  left_c=(int*)malloc(m*sizeof(int));
  right_c=(int*)malloc((size-m)*sizeof(int));
  for(i=0;i<m;i++){
    left_a[i]=a[i];
    left_b[i]=b[i];
    left_c[i]=c[i];
  }
  for(i=0;i<size-m;i++){
    right_a[i]=a[i+m];
    right_b[i]=b[i+m];
    right_c[i]=c[i+m];
  }
  sort_a3(left_a,left_b,left_c,m);
  sort_a3(right_a,right_b,right_c,size-m);
  merge3(a,left_a,right_a,b,left_b,right_b,c,left_c,right_c,m,size-m);
  free(left_a);
  free(right_a);
  free(left_b);
  free(right_b);
  free(left_c);
  free(right_c);
  return;
}
void merge3(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int*c,int*left_c,int*right_c,int left_size,int right_size){
  int i = 0, j = 0;
  while (i < left_size|| j < right_size) {
    if (i == left_size) {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      c[i+j] = right_c[j];
      j++;
    } else if (j == right_size) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      c[i+j] = left_c[i];
      i++;
    } else if (left_a[i] <= right_a[j]) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      c[i+j] = left_c[i];
      i++;
    } else {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      c[i+j] = right_c[j];
      j++;
    }
  }
  return;
}
void heap_insert(node *heap,node *elem,int *size,int *heap_list){
  (*size)++;
  int index=(*size);
  while(index>1 && elem->w<heap[index/2].w){
    heap[index]=heap[index/2];
    heap_list[heap[index].u]=index;
    index/=2;
  }
  heap[index]=(*elem);
  heap_list[elem->u]=index;
  return;
}
void heap_update(node *heap,node *elem,int *heap_list){
  int index=heap_list[elem->u];
  while(index>1 && elem->w<heap[index/2].w){
    heap[index]=heap[index/2];
    heap_list[heap[index].u]=index;
    index/=2;
  }
  heap[index]=(*elem);
  heap_list[elem->u]=index;
  return;
}
void heap_read(node *heap,int *size,int *heap_list,node *ans){
  (*ans)=heap[1];
  int index=1;
  while(index*2<*size && heap[*size].w>heap[index*2].w || index*2+1<*size && heap[*size].w>heap[index*2+1].w){
    index=(heap[index*2].w>heap[index*2+1].w)?index*2+1:index*2;
    heap[index/2]=heap[index];
    heap_list[heap[index].u]=index/2;
  }
  heap[index]=heap[*size];
  heap_list[heap[index].u]=index;
  (*size)--;
  return;
}
int get_i(long long*a,long long num,int size){
  if(size==0)
    return 0;
  if(num>=med(a,size))
    return get_i(&a[(size+1)>>1],num,size>>1)+((size+1)>>1);
  else
    return get_i(a,num,(size-1)>>1);
}
long long med(long long*a,int size){
  return a[(size-1)>>1];
}
void range_increment(int i,int j,long long val,long long*tree,int N){
  for(i+=N,j+=N;i<=j;i=(i+1)/2,j=(j-1)/2){
    if(i%2 && (tree[i]==-1 || tree[i]>val)) tree[i] = val;
    if(j%2==0 && (tree[j]==-1 || tree[j]>val)) tree[j] = val;
  }
  return;
}
long long query(int i,long long*tree,int N){
  long long ans=-1,j;
  for(j = i + N; j; j /= 2)
    if(ans==-1 || ans>tree[j] && tree[j]!=-1)
      ans=tree[j];
  return ans;
}
void DJ(int N,int M,int*u,int*v,int*w,int*v_right,int*list_index,int*left_index,int*right_index,int S,long long*d,int*bridge,int*island){
  int i,next_solve,heap_size=0,*heap_list,island_num;
  node elem,*heap;
  heap=(node*)malloc(N*sizeof(node));
  heap_list=(int*)malloc(N*sizeof(int));
  d[S]=0;
  island[S]=0;
  next_solve=S;
  while(1){
    for(i=left_index[next_solve];i>=0 && i<M && u[i]==next_solve;i++)
      if(d[v[i]]==-1 || d[v[i]]>d[next_solve]+w[i]){
        elem.u=v[i];
        elem.w=d[next_solve]+w[i];
        if(d[v[i]]==-1)
          heap_insert(heap,&elem,&heap_size,heap_list);
        else
          heap_update(heap,&elem,heap_list);
        d[v[i]]=d[next_solve]+w[i];
        if(bridge[i]==2)
          island[v[i]]=island[next_solve]+1;
        else
          island[v[i]]=island[next_solve];
      }
      else if(d[v[i]]==d[next_solve]+w[i]){
        if(bridge[i]==2)
          island_num=island[next_solve]+1;
        else
          island_num=island[next_solve];
        if(island[v[i]]>island_num)
          island[v[i]]=island_num;
      }
    for(i=right_index[next_solve];i>=0 && i<M && v_right[i]==next_solve;i++)
      if(d[u[list_index[i]]]==-1 || d[u[list_index[i]]]>d[next_solve]+w[list_index[i]]){
        elem.u=u[list_index[i]];
        elem.w=d[next_solve]+w[list_index[i]];
        if(d[u[list_index[i]]]==-1)
          heap_insert(heap,&elem,&heap_size,heap_list);
        else
          heap_update(heap,&elem,heap_list);
        d[u[list_index[i]]]=d[next_solve]+w[list_index[i]];
        if(bridge[list_index[i]]==2)
          island[u[list_index[i]]]=island[next_solve]+1;
        else
          island[u[list_index[i]]]=island[next_solve];
      }
      else if(d[u[list_index[i]]]==d[next_solve]+w[list_index[i]]){
        if(bridge[list_index[i]]==2)
          island_num=island[next_solve]+1;
        else
          island_num=island[next_solve];
        if(island[u[list_index[i]]]>island_num)
          island[u[list_index[i]]]=island_num;
      }
    if(heap_size==0)
      break;
    heap_read(heap,&heap_size,heap_list,&elem);
    next_solve=elem.u;
  }
  free(heap);
  free(heap_list);
  return;
}
