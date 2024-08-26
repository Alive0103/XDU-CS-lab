#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 5

// 寻找长度为3的回路
void find(int matrix[MAX_NODES][MAX_NODES], int n) {
    int i, j, k;
    char nodes[MAX_NODES] = {'a', 'b', 'c', 'd', 'e'};
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                // 判断是否存在长度为3的回路
                if (matrix[i][j] && matrix[j][k] && matrix[k][i]) {
                    printf("%c %c %c %c\n", nodes[i], nodes[j], nodes[k], nodes[i]);
                }
            }
        }
    }
}

// 判断是否存在长度为3的回路
bool has(int adj_matrix[MAX_NODES][MAX_NODES], int n) {
    int i, j, k;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                // 判断是否存在长度为3的回路
                if (adj_matrix[i][j] && adj_matrix[j][k] && adj_matrix[k][i]) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

int main() {
    int N, i, j, matrix[MAX_NODES][MAX_NODES];
    
    // 输入结点数
    scanf("%d", &N);
    
    // 输入邻接矩阵
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    // 判断并输出长度为3的回路
    if (has(matrix, N)) {
        find(matrix, N);
    } else {
        printf("Does not exist");
    }
    
    return 0;
}

