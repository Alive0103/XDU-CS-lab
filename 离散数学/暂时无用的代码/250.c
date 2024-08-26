#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 10

void dfs(int node, int graph[MAX_NODES][MAX_NODES], bool visited[MAX_NODES], bool strongComponent[MAX_NODES]) {
    visited[node] = true;
    strongComponent[node] = true;
    int i;
    for (i = 0; i < MAX_NODES; i++) {
        if (graph[node][i] == 1 && !visited[i]) {
            dfs(i, graph, visited, strongComponent);
        }
    }
}

void findStrongComponents(int graph[MAX_NODES][MAX_NODES]) {
    bool visited[MAX_NODES] = { false };
    bool strongComponent[MAX_NODES] = { false };
    int i;
    for (i = 0; i < MAX_NODES; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited, strongComponent);
        }
    }
    
    bool isConnected = true;
    for (i = 0; i < MAX_NODES; i++) {
        if (!strongComponent[i]) {
            isConnected = false;
            break;
        }
    }
    
    if (isConnected) {
        printf("Strongly Connected Graph\n");
    } else {
        bool printed[MAX_NODES] = { false };
        
        printf("%d", 1);
        printed[1 - 1] = true;
        
        for (i = 2; i <= MAX_NODES; i++) {
            if (!strongComponent[i - 1] && !printed[i - 1]) {
                printf(" %d", i);
                printed[i - 1] = true;
            }
        }
        
        printf("\n");
        
        for (i = 2; i <= MAX_NODES; i++) {
            if (strongComponent[i - 1]) {
                printf("%d", i);
                printed[i - 1] = true;
                int j;
                for (j = i + 1; j <= MAX_NODES; j++) {
                    if (!strongComponent[j - 1] && !printed[j - 1]) {
                        printf(" %d", j);
                        printed[j - 1] = true;
                    }
                }
                
                printf("\n");
            }
        }
    }
}

int main() {
    int graph[MAX_NODES][MAX_NODES];
    int i, j;
    for (i = 0; i < MAX_NODES; i++) {
        for (j = 0; j < MAX_NODES; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    findStrongComponents(graph);
    
    return 0;
}

