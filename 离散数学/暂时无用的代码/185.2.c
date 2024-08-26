#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateRelations(char* elements, int n) {
    int size = 1 << (n * n); // 2^(n*n)
    char** relations = (char**)malloc(size * sizeof(char*));
    int count = 0;int i,j,k;

    // Generate all possible relations
    for (i = 0; i < size; i++) {
        char* relation = (char*)malloc((n * n + 1) * sizeof(char));
        int k = i;
        for ( j = 0; j < n * n; j++) {
            relation[j] = (k & 1) ? '1' : '0';
            k >>= 1;
        }
        relation[n * n] = '\0';
        relations[count++] = relation;
    }

    // Check for reflexive relations
    printf("zifan:\n");
    for ( i = 0; i < count; i++) {
        int reflexive = 1;
        for ( j = 0; j < n; j++) {
            if (relations[i][j * (n + 1)] != '1') {
                reflexive = 0;
                break;
            }
        }
        if (reflexive) {
            printf("%s\n", relations[i]);
        }
    }

    // Check for symmetric relations
    printf("duichen:\n");
    for ( i = 0; i < count; i++) {
        int symmetric = 1;
        for ( j = 0; j < n; j++) {
            for ( k = 0; k < n; k++) {
                if (relations[i][j * n + k] != relations[i][k * n + j]) {
                    symmetric = 0;
                    break;
                }
            }
            if (!symmetric) {
                break;
            }
        }
        if (symmetric) {
            printf("%s\n", relations[i]);
        }
    }

    // Free allocated memory
    for ( i = 0; i < count; i++) {
        free(relations[i]);
    }
    free(relations);
}

int main() {
    int n;
    scanf("%d", &n);

    char elements[4];
    scanf("{%[^}]", elements);

    generateRelations(elements, n);

    return 0;
}

