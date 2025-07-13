#include <stdio.h>

#define MAX 5

int adj[MAX][MAX];  // Adjacency matrix
int visited[MAX];
int discovery[MAX], finish[MAX];
int time = 0;

// DFS function with timestamps
void DFS(int u, int n) {
    visited[u] = 1;
    discovery[u] = ++time;

    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) {
            DFS(v, n);
        }
    }

    finish[u] = ++time;
}

int main() {
    int n = 5;  // number of users/nodes

    // Initializing adjacency matrix
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            adj[i][j] = 0;

    // Filling the adjacency list:
    adj[0][1] = 1;
    adj[0][2] = 1;
    adj[1][3] = 1;
    adj[2][4] = 1;

    // Initialize visited array
    for (int i = 0; i < MAX; i++)
        visited[i] = 0;

    // Perform DFS from user 0
    DFS(0, n);

    // Print discovery and finish times
    printf("User\tDiscovery\tFinish\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i, discovery[i], finish[i]);
    }

    return 0;
}
