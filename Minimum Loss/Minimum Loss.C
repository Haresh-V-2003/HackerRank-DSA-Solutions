#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


typedef struct {
	long int val;
	int pos;
} node_t;

int cmpfunc(const void * a, const void * b)
{
	long int diff = ((node_t*)b)->val - ((node_t*)a)->val;
	if(diff < 0)
		return -1;
	else if(diff > 0)
		return 1;
	return 0;
}

int minimumLoss(int price_size, long int* price)
{
	node_t* pricenodes = malloc(sizeof(node_t)*price_size);

	for(int i=0; i<price_size; ++i) {
		pricenodes[i].val = price[i];
		pricenodes[i].pos = i;
	}

	// Reverse sort
	qsort(pricenodes, price_size, sizeof(*pricenodes), cmpfunc);

	long int curmin = -1;

	for(int i=1; i<price_size; ++i)
		if(pricenodes[i].pos > pricenodes[i-1].pos)
			if(-1 == curmin || curmin > pricenodes[i-1].val - pricenodes[i].val)
				curmin = pricenodes[i-1].val - pricenodes[i].val;

	return curmin;
}

int main() {
    int n; 
    scanf("%i", &n);
    long int *price = malloc(sizeof(long int) * n);
    for (int price_i = 0; price_i < n; price_i++) {
       scanf("%li",&price[price_i]);
    }
    int result = minimumLoss(n, price);
    printf("%d\n", result);
    return 0;
}
