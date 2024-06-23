#include <stdio.h>
#include <stdlib.h>
typedef struct _tree_node{
  enum {red,black} colour;
  long long data;
  int count;
  struct _tree_node *left,*right,*parent;
}tree_node;
void add_num(long long num,long long **dp,tree_node **root,int K);
int bin(int n,int k);
long long get_min(tree_node *root);
void left_rotate(tree_node **root,tree_node *x);
void right_rotate(tree_node **root,tree_node *y);
void reconstruct(tree_node **root,tree_node *x);
int normal_insert(tree_node **root,tree_node *x);
void insert(tree_node **root,tree_node *x);
void delete(tree_node **root,tree_node *head,long long data);
void clean_tree(tree_node *root);

int main (){
  int T,N,K,C,i;
  long long a,min,**dp;
  tree_node *root,*node;
  dp=(long long**)malloc(1000*sizeof(long long*));
  for(i=0;i<1000;i++)
    dp[i]=(long long*)malloc(50000*sizeof(long long));
  scanf("%d",&T);
  while(T--){
    root=NULL;
    scanf("%d%d",&N,&K);
    for(i=0;i<K;i++)
      dp[i][0]=0;
    C=bin(N+K-1,K);
    for(i=0;i<C;i++){
      scanf("%lld",&a);
      node=(tree_node*)malloc(sizeof(tree_node));
      node->data=a;
      node->count=1;
      node->left=node->right=node->parent=NULL;
      insert(&root,node);
    }
    min=get_min(root);
    min/=K;
    printf("%lld ",min);
    add_num(min,dp,&root,K);
    for(i=1;i<N;i++){
      a=get_min(root);
      a-=min*(K-1);
      printf("%lld ",a);
      if(i<N-1)
        add_num(a,dp,&root,K);
    }
    clean_tree(root);
    printf("\n");
  }
  return 0;
}
void add_num(long long num,long long **dp,tree_node **root,int K){
  int i,j,k;
  dp[0][0]++;
  dp[0][dp[0][0]]=num;
  if(K==1){
    delete(root,*root,num);
    return;
  }
  for(j=K-1;j>=0;j--)
    for(k=1;k<=dp[j][0];k++)
      delete(root,*root,dp[j][k]+num*(K-1-j));
  for(i=K-2;i>0;i--)
    for(j=i-1;j>=0;j--)
      for(k=1;k<=dp[j][0];k++){
        dp[i][0]++;
        dp[i][dp[i][0]]=dp[j][k]+num*(i-j);
      }
  return;
}
int bin(int n,int k){
  if(k>n-k)
    k=n-k;
  int p=1,i;
  for(i=1;i<=k;++i){
    p*=n+1-i;
    p/=i;
  }
  return p;
}
long long get_min(tree_node *root){
  if(!root)
    return -1;
  while(root->left)
    root=root->left;
  return root->data;
}
void left_rotate(tree_node **root,tree_node *x){
  tree_node *y;
  y=x->right;
  if(!y) return;
  x->right=y->left;
  if(y->left)
    y->left->parent=x;
  y->parent=x->parent;
  if(x->parent==NULL) *root=y;
  else
    if(x==x->parent->left)
      x->parent->left=y;
    else
      x->parent->right=y;
  y->left=x;
  x->parent=y;
  return;
}
void right_rotate(tree_node **root,tree_node *y){
  tree_node *x;
  x=y->left;
  if(!x) return;
  y->left=x->right;
  if(x->right)
    x->right->parent=y;
  x->parent=y->parent;
  if(y->parent==NULL) *root=x;
  else
    if(y==y->parent->right)
      y->parent->right=x;
    else
      y->parent->left=x;
  x->right=y;
  y->parent=x;
  return;
}
void reconstruct(tree_node **root,tree_node *x){
  tree_node *y,*z;
  y=x->parent;
  z=x->parent->parent;
  x->colour=black;
  z->colour=red;
  x->parent=z->parent;
  if(z->parent==NULL)
    *root=x;
  else if(z==z->parent->left)
    z->parent->left=x;
  else
    z->parent->right=x;
  if(z->left==y){
    x->left=y;
    x->right=z;
  }
  else{
    x->left=z;
    x->right=y;
  }
  y->parent=z->parent=x;
  y->left=y->right=z->left=z->right=NULL;
  return;
}
int normal_insert(tree_node **root,tree_node *x){
  if(*root==NULL)
    *root=x;
  else if((*root)->data==x->data){
    (*root)->count++;
    free(x);
    return 0;
  }
  else{
    x->parent=*root;
    if((*root)->data>x->data)
      return normal_insert(&((*root)->left),x);
    else
      return normal_insert(&((*root)->right),x);
  }
  return 1;
}
void insert(tree_node **root,tree_node *x){
  if(!normal_insert(root,x))
    return;
  tree_node *y;
  x->colour=red;
  while(x!=*root && x->parent->colour==red){
    if(x->parent==x->parent->parent->left){
      y=x->parent->parent->right;
      if(!y)
        if(x==x->parent->left){
          x->parent->colour=black;
          x->parent->parent->colour=red;
          right_rotate(root,x->parent->parent);
        }
        else{
          y=x->parent;
          reconstruct(root,x);
          x=y;
        }
      else if(y->colour==red){
        x->parent->colour=black;
        y->colour=black;
        x->parent->parent->colour=red;
        x=x->parent->parent;
      }
      else{
        if(x==x->parent->right){
          x=x->parent;
          left_rotate(root,x);
        }
        x->parent->colour=black;
        x->parent->parent->colour=red;
        right_rotate(root,x->parent->parent);
      }
    }
    else{
      y=x->parent->parent->left;
      if(!y)
        if(x==x->parent->right){
          x->parent->colour=black;
          x->parent->parent->colour=red;
          left_rotate(root,x->parent->parent);
        }
        else{
          y=x->parent;
          reconstruct(root,x);
          x=y;
        }
      else if(y->colour==red){
        x->parent->colour=black;
        y->colour=black;
        x->parent->parent->colour=red;
        x=x->parent->parent;
      }
      else{
        if(x==x->parent->left){
          x=x->parent;
          right_rotate(root,x);
        }
        x->parent->colour=black;
        x->parent->parent->colour=red;
        left_rotate(root,x->parent->parent);
      }
    }
  }
  (*root)->colour=black;
  return;
}
void delete(tree_node **root,tree_node *head,long long data){
  tree_node *db,*parent,*brother,*child;
  if(!head)
    return;
  if(data<head->data){
    delete(root,head->left,data);
    return;
  }
  if(data>head->data){
    delete(root,head->right,data);
    return;
  }
  if(data==head->data){
    if(head->count>1){
      head->count--;
      return;
    }
    if(head->left && head->right){
      db=head->right;
      while(db->left)
        db=db->left;
      head->data=db->data;
      head->count=db->count;
      head=db;
    }
    if(head->left==NULL && head->right==NULL){
      parent=head->parent;
      if(!parent){
        *root=NULL;
        free(head);
        return;
      }
      brother=(parent->left==head)?parent->right:parent->left;
      if(parent->left==head)
        parent->left=NULL;
      else
        parent->right=NULL;
      free(head);
      if(brother)
        return;
      else
        db=parent;
    }
    else{
      parent=head->parent;
      child=(!head->left)?head->right:head->left;
      if(!parent){
        *root=child;
        child->parent=NULL;
        child->colour=black;
        free(head);
        return;
      }
      if(parent->left==head)
        parent->left=child;
      else
        parent->right=child;
      child->parent=parent;
      db=parent;
      free(head);
    }
  }
  while(db){
    if(db->colour==red){
      db->colour=black;
      return;
    }
    if(db==*root)
      return;
    parent=db->parent;
    brother=(parent->left==db)?parent->right:parent->left;
    if(!brother)
      db=parent;
    else if(brother==parent->right){
      if(brother->colour==black && brother->right && brother->right->colour==red){
        brother->colour=parent->colour;
        brother->right->colour=black;
        parent->colour=black;
        left_rotate(root,parent);
        return;
      }
      else if(brother->colour==black && brother->left && brother->left->colour==red){
        brother->left->colour=parent->colour;
        parent->colour=black;
        right_rotate(root,brother);
        left_rotate(root,parent);
        return;
      }
      else if(brother->colour==black){
        brother->colour=red;
        db=parent;
      }
      else{
        brother->colour=black;
        parent->colour=red;
        left_rotate(root,parent);
      }
    }
    else{
      if(brother->colour==black && brother->left && brother->left->colour==red){
        brother->colour=parent->colour;
        brother->left->colour=black;
        parent->colour=black;
        right_rotate(root,parent);
        return;
      }
      else if(brother->colour==black && brother->right && brother->right->colour==red){
        brother->right->colour=parent->colour;
        parent->colour=black;
        left_rotate(root,brother);
        right_rotate(root,parent);
        return;
      }
      else if(brother->colour==black){
        brother->colour=red;
        db=parent;
      }
      else{
        brother->colour=black;
        parent->colour=red;
        right_rotate(root,parent);
      }
    }
  }
  return;
}
void clean_tree(tree_node *root){
  if(!root)
    return;
  clean_tree(root->left);
  clean_tree(root->right);
  free(root);
  return;
}
