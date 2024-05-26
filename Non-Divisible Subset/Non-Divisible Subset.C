#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n;
    int k;
    int a[101] = {};
    scanf("%d", &n);
    scanf("%d", &k);
    for (int i = 0; i < n; i++) {
        int tmp;
        scanf("%d", &tmp);
        a[tmp % k]++;
    }
    int count = 0;
    if (a[0] > 0)
        count++;
    if (k % 2 == 0 && a[k / 2] > 0)
        count++;
    for (int i = 1, j = k - 1; i < j; i++, j--) {
        if (a[i] > a[j])
            count += a[i];
        else
            count += a[j];
    }
    printf("%d\n", count);
    return 0;
}
