#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

int** makeGraph(int p, int q, int startv, int *result_count){
    if(p == 0){
        *result_count = 1;
        int** toreturn = malloc(sizeof(int*));
        toreturn[0] = malloc(2*sizeof(int));
        toreturn[0][0] = 0;
        toreturn[0][1] = 0;
        return toreturn;
    }
    if(q == 2){
        int numspokes = 3;
        while(numspokes*(numspokes - 1)*(numspokes - 2) <= 6*p){
            numspokes++;
        }
        numspokes--;

        int tempresult_count;
        int** graph = makeGraph(p - (numspokes*(numspokes - 1)*(numspokes - 2))/6, q, startv + 1 + numspokes, &tempresult_count);
        *result_count = tempresult_count + numspokes;
        graph = realloc(graph, (*result_count)*sizeof(int*));
        for(int i = 0; i < numspokes; i++){
            graph[tempresult_count + i] = malloc(2*sizeof(int));
            graph[tempresult_count + i][0] = startv + 1;
            graph[tempresult_count + i][1] = startv + i + 2;
        }
        graph[0][0] += numspokes + 1;
        graph[0][1] += numspokes;
        return graph;
    }
    else{
        int factor1[q - 2];
        int factor2[q - 2];
        int factor3[q - 2];
        int currp = p;
        int extranum = 3*(q - 2);
        for(int i = 0; i < q - 2; i++){
            if(currp == 0){
                factor1[i] = 0;
                factor2[i] = 0;
                factor3[i] = 0;
            }
            else{
                factor1[i] = 1;
                while(factor1[i]*factor1[i]*factor1[i] <= currp){
                    factor1[i]++;
                }
                factor1[i]--;
                factor2[i] = factor1[i];
                while(factor1[i]*factor2[i]*factor2[i] <= currp){
                    factor2[i]++;
                }
                factor2[i]--;
                factor3[i] = factor2[i];
                while(factor1[i]*factor2[i]*factor3[i] <= currp){
                    factor3[i]++;
                }
                factor3[i]--;
                currp -= factor1[i]*factor2[i]*factor3[i];
                extranum += factor1[i] + factor2[i] + factor3[i];
            }
        }

        int tempresult_count;
        int** graph = makeGraph(currp, q, startv + extranum, &tempresult_count);
        *result_count = tempresult_count + extranum;
        graph = realloc(graph, (*result_count)*sizeof(int*));
        graph[tempresult_count] = malloc(2*sizeof(int));
        graph[tempresult_count][0] = startv + 1;
        graph[tempresult_count][1] = startv + 3*(q - 2);
        for(int i = 0; i < 3*(q - 2) - 1; i++){
            graph[tempresult_count + i + 1] = malloc(2*sizeof(int));
            graph[tempresult_count + i + 1][0] = startv + i + 1;
            graph[tempresult_count + i + 1][1] = startv + i + 2;
        }
        int index = tempresult_count + 3*(q - 2);
        int numvertex = 3*(q - 2);
        for(int i = 0; i < q - 2; i++){
            for(int j = 0; j < factor1[i]; j++){
                graph[index] = malloc(2*sizeof(int));
                graph[index][0] = startv + i + 1;
                graph[index][1] = startv + numvertex + 1;
                index++;
                numvertex++;
            }
            for(int j = 0; j < factor2[i]; j++){
                graph[index] = malloc(2*sizeof(int));
                graph[index][0] = startv + (q - 2) + i + 1;
                graph[index][1] = startv + numvertex + 1;
                index++;
                numvertex++;
            }
            for(int j = 0; j < factor3[i]; j++){
                graph[index] = malloc(2*sizeof(int));
                graph[index][0] = startv + 2*(q - 2) + i + 1;
                graph[index][1] = startv + numvertex + 1;
                index++;
                numvertex++;
            }
        }

        graph[0][0] += extranum;
        graph[0][1] += extranum;
        return graph;
    }    
}

int main()
{
    char** PQ = split_string(readline());

    char* P_endptr;
    char* P_str = PQ[0];
    int P = strtol(P_str, &P_endptr, 10);

    if (P_endptr == P_str || *P_endptr != '\0') { exit(EXIT_FAILURE); }

    char* Q_endptr;
    char* Q_str = PQ[1];
    int Q = strtol(Q_str, &Q_endptr, 10);

    if (Q_endptr == Q_str || *Q_endptr != '\0') { exit(EXIT_FAILURE); }

    int result_count;
    int** result = makeGraph(P, Q, 0, &result_count);
    for(int i = 0; i < result_count; i++){
        printf("%d %d\n", result[i][0], result[i][1]);
    }
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
