#include<stdio.h>
#include<string.h>
int dp[5001][5001];
int main(){
    char st1[5001], st2[5001];
    scanf("%s", st1);
    scanf("%s", st2);
    int m = strlen(st1), n = strlen(st2), i, j;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            if(st1[i-1] == st2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = dp[i][j-1] > dp[i-1][j] ? dp[i][j-1] : dp[i-1][j];
    printf("%d", dp[m][n]);
    return 0;
}
