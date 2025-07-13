#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 128
#define MAX_LEN 100

typedef struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

typedef struct MinHeap {
    unsigned size;
    MinHeapNode* array[MAX_CHAR];
} MinHeap;

// Function to check if character is a vowel
int isVowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

// Create a new heap node
MinHeapNode* newNode(char data, unsigned freq) {
    MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// Swap two nodes
void swapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify the min-heap
void minHeapify(MinHeap* heap, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < heap->size && heap->array[l]->freq < heap->array[smallest]->freq)
        smallest = l;
    if (r < heap->size && heap->array[r]->freq < heap->array[smallest]->freq)
        smallest = r;

    if (smallest != i) {
        swapNode(&heap->array[i], &heap->array[smallest]);
        minHeapify(heap, smallest);
    }
}

// Build a min-heap
MinHeap* buildMinHeap(char data[], int freq[], int size) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = size;
    for (int i = 0; i < size; i++)
        heap->array[i] = newNode(data[i], freq[i]);

    for (int i = (size - 2) / 2; i >= 0; i--)
        minHeapify(heap, i);

    return heap;
}

// Extract the node with the smallest frequency
MinHeapNode* extractMin(MinHeap* heap) {
    MinHeapNode* temp = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    minHeapify(heap, 0);
    return temp;
}

// Insert a node into the heap
void insertHeap(MinHeap* heap, MinHeapNode* node) {
    int i = heap->size++;
    heap->array[i] = node;

    while (i && node->freq < heap->array[(i - 1) / 2]->freq) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

// Build the Huffman tree
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeap* heap = buildMinHeap(data, freq, size);

    while (heap->size > 1) {
        MinHeapNode* left = extractMin(heap);
        MinHeapNode* right = extractMin(heap);

        MinHeapNode* top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertHeap(heap, top);
    }

    return extractMin(heap);
}

// Generate Huffman codes
void generateCodes(MinHeapNode* root, char* code, int top, char codes[MAX_CHAR][MAX_CHAR]) {
    if (root->left) {
        code[top] = '0';
        generateCodes(root->left, code, top + 1, codes);
    }

    if (root->right) {
        code[top] = '1';
        generateCodes(root->right, code, top + 1, codes);
    }

    if (!root->left && !root->right) {
        code[top] = '\0';
        strcpy(codes[(int)root->data], code);
    }
}

int main() {
    char str[MAX_LEN];
    int freq[MAX_CHAR] = {0};
    char symbols[MAX_CHAR];
    int symCount = 0;

    printf("Enter a string (max 100 chars): ");
    fgets(str, MAX_LEN, stdin);
    str[strcspn(str, "\n")] = 0;  // Remove newline

    // Replace vowels with '*' and count frequency
    for (int i = 0; str[i]; i++) {
        if (isVowel(str[i]))
            str[i] = '*';
        freq[(int)str[i]]++;
    }

    // Create symbols array from non-zero frequencies
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i]) {
            symbols[symCount++] = (char)i;
        }
    }

    // Build Huffman tree
    MinHeapNode* root = buildHuffmanTree(symbols, freq, symCount);

    // Generate codes
    char codes[MAX_CHAR][MAX_CHAR];
    char code[MAX_CHAR];
    generateCodes(root, code, 0, codes);

    // Print Huffman codes
    printf("\nHuffman Codes:\n");
    for (int i = 0; i < symCount; i++) {
        printf("Character '%c': %s\n", symbols[i], codes[(int)symbols[i]]);
    }

    // Encode original string
    printf("\nEncoded Binary String:\n");
    for (int i = 0; str[i]; i++) {
        printf("%s", codes[(int)str[i]]);
    }
    printf("\n");

    return 0;
}
