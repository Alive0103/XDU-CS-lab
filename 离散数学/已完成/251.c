#include <stdio.h>

void print(int root, int a[100][100], int n) {
    printf("%d", root);
    int i;
    for (i = 0; i < n; i++) {
        if (a[root - 1][i] == 1) {
            printf(" (%d,%d)", root, i + 1);
            print(i + 1, a, n);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int i,j; 
    int adjMatrix[100][100];
    for ( i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
    }
    
    int root;
    scanf("%d", &root);
    
    print(root, adjMatrix, n);
    
    return 0;
}

