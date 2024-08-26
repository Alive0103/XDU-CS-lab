#include <stdio.h>
#include <stdbool.h>
#define N 10

bool has_hamiltonian_cycle(int adj_matrix[N][N], int visited[N], int path[N], int v, int count) {
	int i;
    visited[v] = 1;
    path[count] = v;
    if (count == N - 1 && adj_matrix[path[count]][path[0]] == 1) {
        return true;
    }
    for (i = 0; i < N; i++) {
        if (adj_matrix[v][i] == 1 && visited[i] == 0) {
            if (has_hamiltonian_cycle(adj_matrix, visited, path, i, count + 1)) {
                return true;
            }
        }
    }
    visited[v] = 0;
    return false;
}

bool check_hamiltonian_cycle(int adj_matrix[N][N]) {
	int i;
    int visited[N] = {0};
    int path[N] = {0};
    for ( i = 0; i < N; i++) {
        if (has_hamiltonian_cycle(adj_matrix, visited, path, i, 0)) {
            return true;
        }
    }
    return false;
}

int main() {
	int i;
    int adj_matrix[N][N],j;
    for ( i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%1d", &adj_matrix[i][j]);
        }
    }
    bool result = check_hamiltonian_cycle(adj_matrix);
    if (result) {
        printf("True");
    } else {
        printf("False");
    }
    return 0;
}

