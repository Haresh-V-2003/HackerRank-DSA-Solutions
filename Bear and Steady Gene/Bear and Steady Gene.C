#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define LETTER_TO_INDEX(a)  (((a) >> 1) & 0x3)
char lets[] = {
    'A',
    'C',
    'T', 
    'G'
};

int forward[4][500001];
int backward[4][500001];
int lookup[4][500002];

int main() {
    int i, j, n, count;
    char input[500000];
    
    scanf("%d", &n);
    scanf("%s", input);
    for (j = 0; j < 4; j++) {
        for (i = 0; i < n; i++) {
            forward[j][i + 1] = forward[j][i] + (LETTER_TO_INDEX(input[i]) == j);
            backward[j][i + 1] = backward[j][i] + (LETTER_TO_INDEX(input[n - i - 1]) == j);
        }
    }
    
    memset(lookup, -1, sizeof(int) * 4 * 500002);
    for (j = 0; j < 4; j++) {
        lookup[j][0] = n;
        for (i = 1; i <= n; i++) {
            if (backward[j][i] != backward[j][i - 1] || i == n) {
                lookup[j][backward[j][i - 1]] = n - i + 1;
            }
        }
    }
        
    int needed = n / 4;
    int min_len = n;
    int l_max;
    int l_len;
    int pos;
    for (i = 0; i < n; i++) {
        l_max = 0;
        for (j = 0; j < 4; j++) {
            if (forward[j][i] > needed) {
                l_max = -1;
                break;
            } 
            pos = lookup[j][needed - forward[j][i]];
            if (pos > l_max)
                l_max = pos;
        }
        if (l_max != -1 && l_max - i < min_len) {
            min_len = l_max - i;
        }
    }
    printf("%d\n", min_len);
    
    return 0;
}
