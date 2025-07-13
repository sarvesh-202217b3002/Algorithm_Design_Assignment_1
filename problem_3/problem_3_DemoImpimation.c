#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_INTERSECTIONS 100
#define MAX_ROADS 1000

// Structure for adjacency list node (represents a road)
typedef struct Road {
    int destination;
    int roadId;           // Unique identifier for the road
    bool isBlocked;       // Status of the road
    struct Road* next;
} Road;

// Structure for intersection (node in adjacency list)
typedef struct Intersection {
    int id;
    Road* roads;          // List of connected roads
} Intersection;

// Structure for the city graph
typedef struct CityGraph {
    int numIntersections;
    int numRoads;
    Intersection intersections[MAX_INTERSECTIONS];
    bool roadBlocked[MAX_ROADS];  // Global road blocking status
} CityGraph;

// Queue structure for BFS
typedef struct Queue {
    int items[MAX_INTERSECTIONS];
    int front;
    int rear;
    int size;
} Queue;

// Function to create a new road
Road* createRoad(int destination, int roadId) {
    Road* newRoad = (Road*)malloc(sizeof(Road));
    newRoad->destination = destination;
    newRoad->roadId = roadId;
    newRoad->isBlocked = false;
    newRoad->next = NULL;
    return newRoad;
}

// Function to initialize the city graph
void initializeCityGraph(CityGraph* city, int numIntersections) {
    city->numIntersections = numIntersections;
    city->numRoads = 0;
    
    for (int i = 0; i < numIntersections; i++) {
        city->intersections[i].id = i;
        city->intersections[i].roads = NULL;
    }
    
    for (int i = 0; i < MAX_ROADS; i++) {
        city->roadBlocked[i] = false;
    }
}

// Function to add a road (undirected edge)
void addRoad(CityGraph* city, int intersection1, int intersection2) {
    int roadId = city->numRoads++;
    
    // Add road from intersection1 to intersection2
    Road* road1 = createRoad(intersection2, roadId);
    road1->next = city->intersections[intersection1].roads;
    city->intersections[intersection1].roads = road1;
    
    // Add road from intersection2 to intersection1 (undirected)
    Road* road2 = createRoad(intersection1, roadId);
    road2->next = city->intersections[intersection2].roads;
    city->intersections[intersection2].roads = road2;
    
    printf("Road %d added between intersections %d and %d\n", roadId, intersection1, intersection2);
}

// Function to block a road
void blockRoad(CityGraph* city, int intersection1, int intersection2) {
    // Find and block the road between intersection1 and intersection2
    Road* current = city->intersections[intersection1].roads;
    
    while (current != NULL) {
        if (current->destination == intersection2) {
            city->roadBlocked[current->roadId] = true;
            printf("Road %d between intersections %d and %d has been blocked\n", 
                   current->roadId, intersection1, intersection2);
            return;
        }
        current = current->next;
    }
    
    printf("Road between intersections %d and %d not found\n", intersection1, intersection2);
}

// Function to unblock a road
void unblockRoad(CityGraph* city, int intersection1, int intersection2) {
    Road* current = city->intersections[intersection1].roads;
    
    while (current != NULL) {
        if (current->destination == intersection2) {
            city->roadBlocked[current->roadId] = false;
            printf("Road %d between intersections %d and %d has been unblocked\n", 
                   current->roadId, intersection1, intersection2);
            return;
        }
        current = current->next;
    }
    
    printf("Road between intersections %d and %d not found\n", intersection1, intersection2);
}

// Queue operations for BFS
void initializeQueue(Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

bool isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

void enqueue(Queue* queue, int item) {
    if (queue->size < MAX_INTERSECTIONS) {
        queue->rear = (queue->rear + 1) % MAX_INTERSECTIONS;
        queue->items[queue->rear] = item;
        queue->size++;
    }
}

int dequeue(Queue* queue) {
    if (!isQueueEmpty(queue)) {
        int item = queue->items[queue->front];
        queue->front = (queue->front + 1) % MAX_INTERSECTIONS;
        queue->size--;
        return item;
    }
    return -1;
}

// Function to print the city graph
void printCityGraph(CityGraph* city) {
    printf("\n=== CITY ROAD NETWORK ===\n");
    for (int i = 0; i < city->numIntersections; i++) {
        printf("Intersection %d connects to: ", i);
        Road* current = city->intersections[i].roads;
        
        if (current == NULL) {
            printf("(no roads)");
        } else {
            while (current != NULL) {
                char status[20];
                if (city->roadBlocked[current->roadId]) {
                    strcpy(status, "(BLOCKED)");
                } else {
                    strcpy(status, "(OPEN)");
                }
                printf("%d %s ", current->destination, status);
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}

// BFS to check reachability between two intersections
bool isReachable(CityGraph* city, int start, int end) {
    if (start == end) return true;
    
    bool visited[MAX_INTERSECTIONS] = {false};
    Queue queue;
    initializeQueue(&queue);
    
    visited[start] = true;
    enqueue(&queue, start);
    
    printf("BFS Traversal for reachability from %d to %d: ", start, end);
    
    while (!isQueueEmpty(&queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);
        
        Road* road = city->intersections[current].roads;
        while (road != NULL) {
            int neighbor = road->destination;
            
            // Check if road is not blocked and neighbor not visited
            if (!city->roadBlocked[road->roadId] && !visited[neighbor]) {
                if (neighbor == end) {
                    printf("-> %d (FOUND!)\n", neighbor);
                    return true;
                }
                
                visited[neighbor] = true;
                enqueue(&queue, neighbor);
            }
            road = road->next;
        }
    }
    
    printf("(NOT REACHABLE)\n");
    return false;
}

// BFS to find shortest path (minimum number of roads)
int findShortestPath(CityGraph* city, int start, int end) {
    if (start == end) return 0;
    
    bool visited[MAX_INTERSECTIONS] = {false};
    int distance[MAX_INTERSECTIONS];
    int parent[MAX_INTERSECTIONS];
    Queue queue;
    initializeQueue(&queue);
    
    // Initialize distances and parents
    for (int i = 0; i < city->numIntersections; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    
    visited[start] = true;
    distance[start] = 0;
    enqueue(&queue, start);
    
    printf("BFS for shortest path from %d to %d:\n", start, end);
    printf("Traversal order: ");
    
    while (!isQueueEmpty(&queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);
        
        if (current == end) {
            printf("(DESTINATION REACHED!)\n");
            break;
        }
        
        Road* road = city->intersections[current].roads;
        while (road != NULL) {
            int neighbor = road->destination;
            
            // Check if road is not blocked and neighbor not visited
            if (!city->roadBlocked[road->roadId] && !visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;
                enqueue(&queue, neighbor);
            }
            road = road->next;
        }
    }
    
    // Print the path if destination is reachable
    if (distance[end] != INT_MAX) {
        printf("Shortest path: ");
        int path[MAX_INTERSECTIONS];
        int pathLength = 0;
        int current = end;
        
        while (current != -1) {
            path[pathLength++] = current;
            current = parent[current];
        }
        
        for (int i = pathLength - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
        
        return distance[end];
    }
    
    return -1; // No path found
}

// BFS to count connected components
int countConnectedComponents(CityGraph* city) {
    bool visited[MAX_INTERSECTIONS] = {false};
    int componentCount = 0;
    
    printf("=== CONNECTED COMPONENTS ANALYSIS ===\n");
    
    for (int i = 0; i < city->numIntersections; i++) {
        if (!visited[i]) {
            componentCount++;
            printf("Component %d: ", componentCount);
            
            // BFS to find all intersections in this component
            Queue queue;
            initializeQueue(&queue);
            
            visited[i] = true;
            enqueue(&queue, i);
            printf("%d ", i);
            
            while (!isQueueEmpty(&queue)) {
                int current = dequeue(&queue);
                
                Road* road = city->intersections[current].roads;
                while (road != NULL) {
                    int neighbor = road->destination;
                    
                    if (!city->roadBlocked[road->roadId] && !visited[neighbor]) {
                        visited[neighbor] = true;
                        enqueue(&queue, neighbor);
                        printf("%d ", neighbor);
                    }
                    road = road->next;
                }
            }
            printf("\n");
        }
    }
    
    return componentCount;
}

// Function to run comprehensive tests
void runTests(CityGraph* city) {
    printf("=== COMPREHENSIVE TESTING ===\n\n");
    
    // Test 1: Check reachability
    printf("Test 1: Reachability Analysis\n");
    printf("Can travel from 0 to 4? %s\n", isReachable(city, 0, 4) ? "YES" : "NO");
    printf("Can travel from 1 to 5? %s\n", isReachable(city, 1, 5) ? "YES" : "NO");
    printf("\n");
    
    // Test 2: Find shortest paths
    printf("Test 2: Shortest Path Analysis\n");
    int dist1 = findShortestPath(city, 0, 4);
    printf("Shortest distance from 0 to 4: %d roads\n", dist1);
    
    int dist2 = findShortestPath(city, 1, 3);
    printf("Shortest distance from 1 to 3: %d roads\n", dist2);
    printf("\n");
    
    // Test 3: Count connected components
    printf("Test 3: Connected Components\n");
    int components = countConnectedComponents(city);
    printf("Total connected components: %d\n\n", components);
    
    // Test 4: Block some roads and test again
    printf("Test 4: Blocking Roads and Re-testing\n");
    blockRoad(city, 1, 2);
    blockRoad(city, 2, 3);
    
    printCityGraph(city);
    
    printf("After blocking roads:\n");
    printf("Can travel from 0 to 4? %s\n", isReachable(city, 0, 4) ? "YES" : "NO");
    
    int newComponents = countConnectedComponents(city);
    printf("Connected components after blocking: %d\n\n", newComponents);
    
    // Test 5: Unblock roads
    printf("Test 5: Unblocking Roads\n");
    unblockRoad(city, 1, 2);
    unblockRoad(city, 2, 3);
    
    printf("After unblocking roads:\n");
    int finalComponents = countConnectedComponents(city);
    printf("Connected components after unblocking: %d\n", finalComponents);
}

// Interactive menu system
void displayMenu() {
    printf("\n=== SMART CITY NAVIGATION SYSTEM ===\n");
    printf("1. Check reachability between two intersections\n");
    printf("2. Find shortest path between two intersections\n");
    printf("3. Count connected components\n");
    printf("4. Block a road\n");
    printf("5. Unblock a road\n");
    printf("6. Display city network\n");
    printf("7. Run comprehensive tests\n");
    printf("8. Exit\n");
    printf("Choose an option: ");
}

int main() {
    CityGraph city;
    
    printf("=== SMART CITY NAVIGATION SYSTEM ===\n");
    printf("Graph-based Road Network Analysis\n\n");
    
    // Initialize city with sample data
    initializeCityGraph(&city, 6);
    
    // Create sample road network
    printf("Creating sample city network...\n");
    addRoad(&city, 0, 1);  // Road 0
    addRoad(&city, 0, 2);  // Road 1
    addRoad(&city, 1, 2);  // Road 2
    addRoad(&city, 1, 3);  // Road 3
    addRoad(&city, 2, 3);  // Road 4
    addRoad(&city, 2, 4);  // Road 5
    addRoad(&city, 3, 4);  // Road 6
    addRoad(&city, 5, 5);  // Road 7 (isolated intersection - self loop for demo)
    
    printCityGraph(&city);
    
    // Interactive menu
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int start, end;
                printf("Enter start intersection: ");
                scanf("%d", &start);
                printf("Enter end intersection: ");
                scanf("%d", &end);
                
                if (start >= 0 && start < city.numIntersections && 
                    end >= 0 && end < city.numIntersections) {
                    bool reachable = isReachable(&city, start, end);
                    printf("Result: %s\n", reachable ? "REACHABLE" : "NOT REACHABLE");
                } else {
                    printf("Invalid intersection numbers!\n");
                }
                break;
            }
            
            case 2: {
                int start, end;
                printf("Enter start intersection: ");
                scanf("%d", &start);
                printf("Enter end intersection: ");
                scanf("%d", &end);
                
                if (start >= 0 && start < city.numIntersections && 
                    end >= 0 && end < city.numIntersections) {
                    int distance = findShortestPath(&city, start, end);
                    if (distance != -1) {
                        printf("Shortest distance: %d roads\n", distance);
                    } else {
                        printf("No path exists!\n");
                    }
                } else {
                    printf("Invalid intersection numbers!\n");
                }
                break;
            }
            
            case 3: {
                int components = countConnectedComponents(&city);
                printf("Total connected components: %d\n", components);
                break;
            }
            
            case 4: {
                int int1, int2;
                printf("Enter intersections to block road (int1 int2): ");
                scanf("%d %d", &int1, &int2);
                
                if (int1 >= 0 && int1 < city.numIntersections && 
                    int2 >= 0 && int2 < city.numIntersections) {
                    blockRoad(&city, int1, int2);
                } else {
                    printf("Invalid intersection numbers!\n");
                }
                break;
            }
            
            case 5: {
                int int1, int2;
                printf("Enter intersections to unblock road (int1 int2): ");
                scanf("%d %d", &int1, &int2);
                
                if (int1 >= 0 && int1 < city.numIntersections && 
                    int2 >= 0 && int2 < city.numIntersections) {
                    unblockRoad(&city, int1, int2);
                } else {
                    printf("Invalid intersection numbers!\n");
                }
                break;
            }
            
            case 6:
                printCityGraph(&city);
                break;
                
            case 7:
                runTests(&city);
                break;
                
            case 8:
                printf("Exiting Smart City Navigation System...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
    
    return 0;
}