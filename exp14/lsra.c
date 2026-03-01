#include <stdio.h> 
#define MAX 10 
#define INF 9999 
int main() { 
    int n, i, j, source; 
    int cost[MAX][MAX], dist[MAX], visited[MAX]; 
    // Number of nodes 
    printf("Enter number of nodes: "); 
    scanf("%d", &n); 
    // Cost matrix 
    printf("Enter cost matrix (9999 for no direct link):\n"); 
    for (i = 0; i < n; i++) { 
        for (j = 0; j < n; j++) { 
            scanf("%d", &cost[i][j]); 
        } 
    } 
 
    // Source router 
    printf("Enter source node: "); 
    scanf("%d", &source); 
 
    // Initialization 
    for (i = 0; i < n; i++) { 
        dist[i] = cost[source][i]; 
        visited[i] = 0; 
    } 
    visited[source] = 1; 
    dist[source] = 0; 
    // Dijkstra's Algorithm 
    for (i = 0; i < n - 1; i++) { 
        int min = INF, u = -1; 
        for (j = 0; j < n; j++) { 
            if (!visited[j] && dist[j] < min) { 
                min = dist[j]; 
                u = j; 
            } 
        } 
 
        visited[u] = 1; 
        for (j = 0; j < n; j++) { 
            if (!visited[j] && dist[u] + cost[u][j] < dist[j]) { 
                dist[j] = dist[u] + cost[u][j]; 
            } 
        } 
    } 
 
    // Display shortest paths 
    printf("\nShortest paths from node %d:\n", source); 
    for (i = 0; i < n; i++) { 
        printf("To node %d -> Cost = %d\n", i, dist[i]); 
    } 
    return 0; 
}