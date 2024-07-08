#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
    int val;
    struct node* next;
}node;

node* a[100010]; 
int h[1000010],f[1000010],g[1000010],b[1000010],len,d[1000010],e[1000010];

void swap(int e,int f)
{
    int temp=b[e];
    b[e]=b[f];
    b[f]=temp;
}

node* Insert(node *head,int val)
{
    node* temp;
    temp=(node*)malloc(sizeof(node*));
    temp->val=val;
    temp->next=NULL;
    if(head==NULL)
    {
        head=temp;
        return head;
    }
    temp->next=head;
    return temp;
}

void shift_up(int idx)
{
    if(idx/2<1)
        return;
    if(b[idx]<b[idx/2])
    {
        swap(idx,idx/2);
        shift_up(idx/2);
    }
    return;
}

void shift_down(int idx)
{
    int lc=2*idx,rc=2*idx+1;
    if(lc>len)
        return;
    if(lc==len)
    {
        if(b[idx]>b[len])
            swap(idx,len);
        return;
    }
    if(b[lc]<=b[rc] && b[lc]<b[idx])
    {
        swap(lc,idx);
        shift_down(lc);
    }
    else if(b[rc]<=b[lc] && b[rc]<b[idx])
    {
        swap(rc,idx);
        shift_down(rc);
    }
    return;
}

void insert(int x)
{
    len++;
    b[len]=x;
    shift_up(len);
    return;
}

void delete()
{
    swap(1,len);
    len--;
    shift_down(1);
    return;
} 

int main()
{
    node* temp;
    int x,n,i,l=1,r;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d",&x,&g[1]);
        h[g[1]]=1;
        for(i=2;i<=x;i++)
        {
            scanf("%d",&g[i]);
            a[g[i-1]]=Insert(a[g[i-1]],g[i]);
            d[g[i]]++;
            h[g[i]]=1;
        }
    }
    for(i=1;i<=1000000;i++)
        if(h[i]==1 && d[i]==0)
            insert(i);
    while(len>0)
    {
        r=0;
        temp=a[b[1]];
        while(temp!=NULL)
        {
            x=temp->val;
            d[x]--;
            if(d[x]==0)
                f[r++]=x;
            temp=temp->next;
        }
        e[l++]=b[1];
        delete();
        for(i=0;i<r;i++)
            insert(f[i]);
    }
    for(i=1;i<l;i++)
        printf("%d ",e[i]);
    printf("\n");
    return 0;
}
