#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int t;
    scanf("%d",&t);
    while(t--)
        {
        int n,k;
        scanf("%d %d",&n,&k);
        int i,a[n+1],flag=0;
        if(k==0)
            {
            for(i=1;i<=n;i++)
                printf("%d ",i);
            printf("\n");
        }
        else
        {
            for(i=1;i<k+1;i++)
                {
                int temp=((n-i)/k)+1;
                if(temp%2)
                    {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
                printf("-1\n");
            else
                {
                int j;
                for(i=1;i<k+1;i++)
                    {
                    for(j=i;j<=n-k;j+=2*k)
                        {
                        a[j]=j+k;
                        a[j+k]=j;
                    }
                }
                for(i=1;i<=n;i++)
                    printf("%d ",a[i]);
                printf("\n");
            }
        }
        
    }
    return 0;
}
