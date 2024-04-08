# Minimum Spanning Tree using Kruskal's Algorithm

This program in C++ demonstrates the application of Kruskal's algorithm to determine the Minimum Spanning Tree (MST) of an undirected weighted graph. The algorithm is implemented to accept an adjacency matrix as input.

## Input Format

The input is structured as follows:

The first line holds an integer N, denoting the count of vertices in the graph.
The second line contains an integer M, indicating the number of edges present in the graph.
The subsequent M lines each present three space-separated integers: u v w, representing an edge linking vertices u and v with weight w.
Vertices are labeled from 1 to N.

## Output Format

The program outputs the edges of the Minimum Spanning Tree along with their weights. Each line represents an edge in the MST, with the format:
<source_vertex>--<destination_vertex> Weight: <weight>

Additionally, the output includes the minimum cost of the Minimum Spanning Tree.

### Sample Input:
```
5
7
1 2 1
1 3 2
1 4 3
1 5 4
2 3 5
3 4 6
4 5 7

```

### Sample Output

```
1--2 Weight: 1
1--3 Weight: 2
1--4 Weight: 3
1--5 Weight: 4
Minimum Cost: 10


```



In this example, the MST contains 4 edges.
