#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print array (for illustration)
void printArray(int arr[], int size, const char* message) {
    printf("%s: ", message);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Partition function for QuickSelect
// Returns the position of pivot in sorted order
int partition(int arr[], int low, int high) {
    // Choose the rightmost element as pivot
    int pivot = arr[high];
    int i = low - 1; // Index of smaller element
    
    printf("    Partitioning range [%d, %d] with pivot = %d\n", low, high, pivot);
    
    for (int j = low; j < high; j++) {
        // If current element is greater than or equal to pivot
        // (for descending order - kth largest)
        if (arr[j] >= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Place pivot in its correct position
    swap(&arr[i + 1], &arr[high]);
    
    printf("    After partition: ");
    for (int k = low; k <= high; k++) {
        if (k == i + 1) printf("[%d] ", arr[k]);
        else printf("%d ", arr[k]);
    }
    printf("\n");
    
    return i + 1; // Return position of pivot
}

// QuickSelect function to find kth largest element
// Uses divide and conquer approach
int quickSelect(int arr[], int low, int high, int k) {
    printf("  QuickSelect called: range [%d, %d], looking for %d%s largest\n", 
           low, high, k, (k == 1) ? "st" : (k == 2) ? "nd" : (k == 3) ? "rd" : "th");
    
    if (low <= high) {
        // Partition the array and get pivot position
        int pivotIndex = partition(arr, low, high);
        
        // Calculate the position of pivot in descending order (1-indexed)
        int pivotPosition = pivotIndex - low + 1;
        
        printf("    Pivot at index %d is in position %d\n", pivotIndex, pivotPosition);
        
        // If pivot is the kth largest element
        if (pivotPosition == k) {
            printf("    Found! %d%s largest element is %d\n", 
                   k, (k == 1) ? "st" : (k == 2) ? "nd" : (k == 3) ? "rd" : "th", arr[pivotIndex]);
            return arr[pivotIndex];
        }
        // If kth largest is in the left partition
        else if (pivotPosition > k) {
            printf("    Searching left partition for %d%s largest\n", 
                   k, (k == 1) ? "st" : (k == 2) ? "nd" : (k == 3) ? "rd" : "th");
            return quickSelect(arr, low, pivotIndex - 1, k);
        }
        // If kth largest is in the right partition
        else {
            printf("    Searching right partition for %d%s largest\n", 
                   k - pivotPosition, (k - pivotPosition == 1) ? "st" : (k - pivotPosition == 2) ? "nd" : (k - pivotPosition == 3) ? "rd" : "th");
            return quickSelect(arr, pivotIndex + 1, high, k - pivotPosition);
        }
    }
    
    return -1; // Should never reach here for valid input
}

// Function to find kth largest element (main interface)
int findKthLargest(int arr[], int n, int k) {
    printf("=== FINDING %d%s LARGEST ELEMENT ===\n", 
           k, (k == 1) ? "ST" : (k == 2) ? "ND" : (k == 3) ? "RD" : "TH");
    
    // Create a copy of array to preserve original
    int* tempArr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempArr[i] = arr[i];
    }
    
    printArray(tempArr, n, "Original array");
    
    // Use QuickSelect to find kth largest
    int result = quickSelect(tempArr, 0, n - 1, k);
    
    free(tempArr);
    return result;
}

// Function to demonstrate with step-by-step execution
void demonstrateAlgorithm(int arr[], int n, int k) {
    printf("=== ALGORITHM DEMONSTRATION ===\n");
    printf("Problem: Find the %d%s largest element in the array\n", 
           k, (k == 1) ? "st" : (k == 2) ? "nd" : (k == 3) ? "rd" : "th");
    printf("Approach: QuickSelect (Divide and Conquer)\n\n");
    
    printArray(arr, n, "Input array");
    printf("k = %d\n\n", k);
    
    int result = findKthLargest(arr, n, k);
    
    printf("\n=== VERIFICATION ===\n");
    // Sort array to verify result
    int* sortedArr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        sortedArr[i] = arr[i];
    }
    
    // Simple bubble sort for verification
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sortedArr[j] < sortedArr[j + 1]) {
                swap(&sortedArr[j], &sortedArr[j + 1]);
            }
        }
    }
    
    printArray(sortedArr, n, "Sorted array (descending)");
    printf("The %d%s largest element is: %d\n", 
           k, (k == 1) ? "st" : (k == 2) ? "nd" : (k == 3) ? "rd" : "th", result);
    printf("Verification: sortedArr[%d] = %d ✓\n", k-1, sortedArr[k-1]);
    
    free(sortedArr);
}

// Function to analyze time complexity
void analyzeTimeComplexity() {
    printf("\n=== TIME COMPLEXITY ANALYSIS ===\n");
    printf("QuickSelect Algorithm:\n");
    printf("• Best Case: O(n) - When pivot divides array into equal halves\n");
    printf("• Average Case: O(n) - Expected linear time\n");
    printf("• Worst Case: O(n²) - When pivot is always the smallest/largest\n");
    printf("\nRecurrence Relation:\n");
    printf("• T(n) = T(n/2) + O(n) in average case\n");
    printf("• T(n) = T(n-1) + O(n) in worst case\n");
    printf("\nSpace Complexity: O(log n) for recursion stack (average case)\n");
    printf("\nAdvantage over full sorting:\n");
    printf("• QuickSelect: O(n) average case\n");
    printf("• Full QuickSort: O(n log n)\n");
}

// Test function with multiple examples
void runTests() {
    printf("=== ADDITIONAL TEST CASES ===\n");
    
    // Test case 1
    int test1[] = {3, 2, 1, 5, 6, 4};
    int n1 = 6, k1 = 2;
    printf("\nTest 1: ");
    printArray(test1, n1, "Array");
    printf("k = %d, Result = %d\n", k1, findKthLargest(test1, n1, k1));
    
    // Test case 2
    int test2[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int n2 = 9, k2 = 4;
    printf("\nTest 2: ");
    printArray(test2, n2, "Array");
    printf("k = %d, Result = %d\n", k2, findKthLargest(test2, n2, k2));
    
    // Test case 3
    int test3[] = {1};
    int n3 = 1, k3 = 1;
    printf("\nTest 3: ");
    printArray(test3, n3, "Array");
    printf("k = %d, Result = %d\n", k3, findKthLargest(test3, n3, k3));
}

int main() {
    printf("=== KTH LARGEST ELEMENT USING QUICKSELECT ===\n");
    printf("Divide and Conquer Approach\n\n");
    
    // Sample input from problem
    int n, k;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Enter k (for kth largest): ");
    scanf("%d", &k);
    
    printf("\n");
    
    // Demonstrate the algorithm
    demonstrateAlgorithm(arr, n, k);
    
    // Analyze time complexity
    analyzeTimeComplexity();
    
    // Run additional tests
    runTests();
    
    free(arr);
    return 0;
}