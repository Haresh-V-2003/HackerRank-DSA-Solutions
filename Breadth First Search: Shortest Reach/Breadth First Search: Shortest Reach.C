#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct node
    {
    int data;
    struct node * next;
}node;
typedef struct list
    {
    node * head;
}list;
void Insert(list *A,int src,int des)
{
    node * temp = malloc(sizeof(node));
    temp -> data  = des;
    temp -> next  = A[src].head;
    A[src].head = temp;
}
void BFS(list *A,int src,int n)
{
    node * temp;
    int i,u,level[n],queue[n];
    int front = 0, rear = 0;
    for(i=0;i<n;i++)
    level[i] = -1;
    queue[front++] = src;
    level[src] = 0;
    while(front>rear)
    {
        u = queue[rear++];
        temp = A[u].head;
        while(temp != NULL)
        {
            if(level[temp->data]==-1)
            {
                queue[front++] = temp->data;
                level[temp->data] = level[u] + 6;
            }
            temp = temp->next;
        }
    }
    
    for(i=0;i<n;i++)
    {
        if(i!=src)
        printf("%d ",level[i]);
    }
    printf("\n");
    
}
int main() {

    int i,j,q,n,m,u,v,s;
    list A[1000];
    scanf("%d",&q);
    for(i=0;i<q;i++)
    {
        scanf("%d%d",&n,&m);
        for(j=0;j<n;j++)
            A[j].head = NULL;
        for(j=0;j<m;j++)
        {
            scanf("%d%d",&u,&v);
            Insert(A,u-1,v-1);
            Insert(A,v-1,u-1);
        }
        
        scanf("%d",&s);
        BFS(A,s-1,n);
    }
    return 0;
}
