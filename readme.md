# Algorithm Design Assignment 1

This repository contains multiple C programs demonstrating fundamental algorithm design and analysis concepts, as part of an academic assignment. Each problem focuses on a different classical algorithm or data structure, with code structured for clarity and learning.

## Table of Contents

- [Problem 1: Social Media User Connection Analysis](#problem-1-social-media-user-connection-analysis)
- [Problem 2: Kth Largest Element (QuickSelect)](#problem-2-kth-largest-element-quickselect)
- [Problem 3: Smart City Navigation System](#problem-3-smart-city-navigation-system)
- [Problem 4: Shortest Path (Dijkstra/Bellman-Ford)](#problem-4-shortest-path-dijkstrabellman-ford)
- [Problem 5: Huffman Coding Compression](#problem-5-huffman-coding-compression)

---

## Problem 1: Social Media User Connection Analysis

**File:** `problem_1/problem_1_DemoCode.c`  
This program models a social network as a directed graph and analyzes user connections using Depth-First Search (DFS) with timestamps.

- **Features:**
  - Uses an adjacency list to model users and their "follows" relationships.
  - Performs DFS traversal, recording discovery and finish times for each user.
  - Identifies influential users by analyzing timestamps (deepest in connection chain, leaf nodes).
  - Displays adjacency list, timestamps, and reachability analyses.

- **Sample Output:**
  - Adjacency list representation
  - DFS traversal order with timestamps
  - Table of users' discovery and finish times
  - Analysis of most influential users and leaf nodes

---

## Problem 2: Kth Largest Element (QuickSelect)

**File:** `problem_2/problem_2_DemoCode.c`  
Implements the QuickSelect algorithm to efficiently find the kth largest element in an unsorted array.

- **Features:**
  - Step-by-step demonstration of QuickSelect
  - Preserves the original array
  - Prints array states after each operation for educational purposes

---

## Problem 3: Smart City Navigation System

**File:** `problem_3/problem_3_DemoImpimation.c`  
Simulates a smart city using a graph where intersections are nodes and roads are edges.

- **Features:**
  - Dynamic road network with the ability to block/unblock roads
  - BFS for reachability between intersections
  - Shortest path finder between intersections
  - Connected component analysis (to identify isolated regions)
  - Interactive menu for user-driven simulation and comprehensive tests

---

## Problem 4: Shortest Path (Dijkstra/Bellman-Ford)

**File:** `problem_4/problem_4.c`  
Calculates the shortest path from a source vertex to all other vertices in a weighted graph using a classical shortest path algorithm.

- **Features:**
  - User inputs adjacency matrix and source vertex
  - Prints shortest distance from the source to all vertices

---

## Problem 5: Huffman Coding Compression

**File:** `problem_5/problem_5_demo.c`  
Demonstrates Huffman coding, a greedy algorithm for lossless data compression.

- **Features:**
  - Builds a min-heap and Huffman tree from input characters and frequencies
  - Generates and assigns Huffman codes to each character
  - Prints codes and demonstrates compression

---

## How to Run

Each problem is a standalone C file. Compile and run each file separately:

```sh
gcc -o problem1 problem_1/problem_1_DemoCode.c
./problem1

gcc -o problem2 problem_2/problem_2_DemoCode.c
./problem2

gcc -o problem3 problem_3/problem_3_DemoImpimation.c
./problem3

gcc -o problem4 problem_4/problem_4.c
./problem4

gcc -o problem5 problem_5/problem_5_demo.c
./problem5
```

Some programs may prompt for input; follow the on-screen instructions.

---

## License

This repository is intended for educational purposes.
