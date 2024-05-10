#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int n; 
    scanf("%d",&n);
    int a[n];
    int i,j,t;
    long int c=0;
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
        for(i=0;i<n;i++){
            for(j=n-1;j>0;j--){
                if(a[j]>a[j-1]){
                    t=a[j];
                    a[j]=a[j-1];
                    a[j-1]=t;
                }
            }
        }
        for(int i=0;i<n;i++){
            c=c+(a[i]*(pow(2,i)));
        }
    printf("%ld",c);
    return 0;
}
