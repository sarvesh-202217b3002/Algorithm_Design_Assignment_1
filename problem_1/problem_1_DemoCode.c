#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 100

// Structure for adjacency list node
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Structure for adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure for the graph
struct Graph {
    int numUsers;
    struct AdjList* array;
};

// Global variables for DFS
int discovery[MAX_USERS];
int finish[MAX_USERS];
int visited[MAX_USERS];
int time_counter = 0;

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with n vertices
struct Graph* createGraph(int numUsers) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numUsers = numUsers;
    graph->array = (struct AdjList*)malloc(numUsers * sizeof(struct AdjList));
    
    // Initialize each adjacency list as empty
    for (int i = 0; i < numUsers; ++i) {
        graph->array[i].head = NULL;
    }
    
    return graph;
}

// Function to add an edge to the directed graph (A follows B)
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// DFS function with timestamps
void DFS(struct Graph* graph, int user) {
    // Mark current user as visited and record discovery time
    visited[user] = 1;
    discovery[user] = ++time_counter;
    
    printf("User %d: Discovered at time %d\n", user, discovery[user]);
    
    // Traverse all adjacent users (users that current user follows)
    struct AdjListNode* temp = graph->array[user].head;
    while (temp) {
        int adjUser = temp->dest;
        if (!visited[adjUser]) {
            printf("  User %d follows User %d (exploring...)\n", user, adjUser);
            DFS(graph, adjUser);
        } else {
            printf("  User %d follows User %d (already visited)\n", user, adjUser);
        }
        temp = temp->next;
    }
    
    // Record finish time
    finish[user] = ++time_counter;
    printf("User %d: Finished at time %d\n", user, finish[user]);
}

// Function to initialize arrays
void initialize(int numUsers) {
    for (int i = 0; i < numUsers; i++) {
        visited[i] = 0;
        discovery[i] = 0;
        finish[i] = 0;
    }
    time_counter = 0;
}

// Function to print the adjacency list
void printGraph(struct Graph* graph) {
    printf("=== ADJACENCY LIST REPRESENTATION ===\n");
    for (int i = 0; i < graph->numUsers; ++i) {
        struct AdjListNode* temp = graph->array[i].head;
        printf("User %d follows: ", i);
        if (temp == NULL) {
            printf("(no one)");
        } else {
            while (temp) {
                printf("%d ", temp->dest);
                temp = temp->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Function to display timestamps in tabular format
void displayTimestamps(int numUsers) {
    printf("=== DFS TIMESTAMPS RESULTS ===\n");
    printf("User\tDiscovery Time\tFinish Time\tDuration\tStatus\n");
    printf("----\t--------------\t-----------\t--------\t------\n");
    
    for (int i = 0; i < numUsers; i++) {
        if (visited[i]) {
            int duration = finish[i] - discovery[i];
            printf("%d\t%d\t\t%d\t\t%d\t\tVisited\n", 
                   i, discovery[i], finish[i], duration);
        } else {
            printf("%d\t-\t\t-\t\t-\t\tNot Reachable\n", i);
        }
    }
    printf("\n");
}

// Function to analyze influential users based on timestamps
void analyzeInfluentialUsers(int numUsers) {
    printf("=== INFLUENTIAL USER ANALYSIS ===\n");
    
    // Find users with highest discovery times (most deeply nested)
    int maxDiscovery = 0;
    int deepestUser = -1;
    
    for (int i = 0; i < numUsers; i++) {
        if (visited[i] && discovery[i] > maxDiscovery) {
            maxDiscovery = discovery[i];
            deepestUser = i;
        }
    }
    
    // Find users with smallest duration (likely leaf nodes - influential)
    int minDuration = 999;
    int mostInfluential = -1;
    
    for (int i = 0; i < numUsers; i++) {
        if (visited[i]) {
            int duration = finish[i] - discovery[i];
            if (duration < minDuration) {
                minDuration = duration;
                mostInfluential = i;
            }
        }
    }
    
    printf("Analysis Results:\n");
    printf("1. Most deeply nested user: User %d (discovered at time %d)\n", 
           deepestUser, maxDiscovery);
    printf("   → This user is deep in the connection chain, likely influential\n");
    
    printf("2. User with shortest exploration duration: User %d (duration: %d)\n", 
           mostInfluential, minDuration);
    printf("   → This suggests a leaf node - potentially most influential\n");
    
    // List all leaf nodes (users who don't follow anyone)
    printf("3. Leaf nodes (don't follow anyone - highly influential):\n");
    for (int i = 0; i < numUsers; i++) {
        if (visited[i] && (finish[i] - discovery[i]) == 1) {
            printf("   → User %d (leaf node)\n", i);
        }
    }
    printf("\n");
}

// Function to analyze reachability
void analyzeReachability(int numUsers) {
    printf("=== REACHABILITY ANALYSIS ===\n");
    
    printf("Users reachable from User 0: ");
    for (int i = 0; i < numUsers; i++) {
        if (visited[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    printf("Users NOT reachable from User 0: ");
    int hasUnreachable = 0;
    for (int i = 0; i < numUsers; i++) {
        if (!visited[i]) {
            printf("%d ", i);
            hasUnreachable = 1;
        }
    }
    if (!hasUnreachable) {
        printf("None - all users are reachable!");
    }
    printf("\n\n");
}

int main() {
    printf("=== SOCIAL MEDIA USER CONNECTION ANALYSIS ===\n");
    printf("Using DFS with Timestamps to Identify Influential Users\n\n");
    
    // Create graph with 5 users (0, 1, 2, 3, 4)
    struct Graph* graph = createGraph(5);
    
    // Add edges based on the given adjacency list
    // 0 → 1, 2
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    
    // 1 → 3
    addEdge(graph, 1, 3);
    
    // 2 → 4
    addEdge(graph, 2, 4);
    
    // 3 → (no one)
    // 4 → (no one)
    
    // Print the graph structure
    printGraph(graph);
    
    // Initialize arrays
    initialize(5);
    
    // Perform DFS starting from user 0
    printf("=== DFS TRAVERSAL WITH TIMESTAMPS ===\n");
    printf("Starting DFS from User 0:\n\n");
    
    DFS(graph, 0);
    
    printf("\n");
    
    // Display results in tabular format
    displayTimestamps(5);
    
    // Analyze influential users
    analyzeInfluentialUsers(5);
    
    // Analyze reachability
    analyzeReachability(5);
    
    // Free allocated memory
    free(graph->array);
    free(graph);
    
    return 0;
}