#include <stdio.h>
#define MAX 20
#define INF 9999

void dijkstra(int graph[MAX][MAX], int n, int src) {
    int dist[MAX];       // Shortest distances from src
    int visited[MAX];    // Visited set

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INF, u;

        // Find the vertex with the minimum distance
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        visited[u] = 1;

        // Update dist[v]
        for (int v = 0; v < n; v++) {
            if (!visited[v] &&
                graph[u][v] &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print distances
    printf("Vertex\tShortest Distance from Source %d\n", src);
    for (int i = 0; i < n; i++) {
        printf("%c\t%d\n", 'A' + i, dist[i]);
    }
}

int main() {
    int graph[MAX][MAX], n, src;

    printf("Enter number of vertices (max 20): ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < n; i++) {
        printf("From vertex %c:\n", 'A' + i);
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter source vertex (0 for A, 1 for B, ...): ");
    scanf("%d", &src);

    dijkstra(graph, n, src);

    return 0;
}
