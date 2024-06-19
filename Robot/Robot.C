#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

long robot(int n, int** vp) {
    int logn = 0;
    while(n>>logn > 0){
        logn++;
    }
    
    long* segtree[logn + 1];
    for(int i = 0; i <= logn; i++){
        segtree[i] = malloc(sizeof(long)<<logn);
        for(int j = 0; j < 1<<logn; j++){
            segtree[i][j] = 0;
        }
    }

    long sum = 0;
    
    for(int i = n - 1; i >= 0; i--){
        long start = i + 1;
        long end = i + vp[i][1] + 1;
        
        long currmax = -LONG_MAX/2;
        if(end >= n){
            currmax = 0;
            end = n;
        }
        
        long currval = start;
        int dig = 0;
        printf("Start: %ld End: %ld", start, end);
        
        while((currval>>dig) < (end>>dig)){
            if(((currval>>dig)&1) == 1){
                long check = segtree[dig][currval>>dig];
                currmax = (check > currmax? check : currmax);
                currval += 1<<dig;
            }
            dig++;
        }
        dig--;
        while(dig >= 0){
            if(((end>>dig)&1) == 1){
                long check = segtree[dig][currval>>dig];
                currmax = (check > currmax? check : currmax);
                currval += 1<<dig;
            }
            dig--;
        }
        segtree[0][i] = currmax - vp[i][0];        
        for(int j = 0; j < logn; j++){
            int pos = i>>(j + 1);
            segtree[j + 1][pos] = (segtree[j][2*pos] > segtree[j][2*pos + 1]? segtree[j][2*pos] : segtree[j][2*pos + 1]);
        }
        
        sum += vp[i][0];
    }

    return segtree[0][0] + sum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    int** vp = malloc(n * sizeof(int*));

    for (int vp_row_itr = 0; vp_row_itr < n; vp_row_itr++) {
        *(vp + vp_row_itr) = malloc(2 * (sizeof(int)));

        char** vp_item_temp = split_string(readline());

        for (int vp_column_itr = 0; vp_column_itr < 2; vp_column_itr++) {
            char* vp_item_endptr;
            char* vp_item_str = *(vp_item_temp + vp_column_itr);
            int vp_item = strtol(vp_item_str, &vp_item_endptr, 10);

            if (vp_item_endptr == vp_item_str || *vp_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(vp + vp_row_itr) + vp_column_itr) = vp_item;
        }
    }


    long result = robot(n, vp);

    fprintf(fptr, "%ld\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }
    if(data[data_length - 1] != 0){
        data_length++;
        data = realloc(data, data_length);
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
