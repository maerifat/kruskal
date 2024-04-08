#include <iostream>

using namespace std;

// Structure to represent an edge in the network
struct NetworkEdge {
    int start, end, weight;
};

// Function to find the root of a vertex in the Union-Find algorithm
int findRoot(int parents[], int vertex) {
    if (parents[vertex] == vertex)
        return vertex;
    return findRoot(parents, parents[vertex]);
}

// Function to merge two sets of vertices
void uniteSets(int parents[], int x, int y) {
    int rootX = findRoot(parents, x);
    int rootY = findRoot(parents, y);
    parents[rootX] = rootY;
}

// Function to implement heapify
void adjustHeap(NetworkEdge arr[], int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < size && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != index) {
        swap(arr[index], arr[largest]);
        adjustHeap(arr, size, largest);
    }
}

// Function to implement heap sort
void heapSort(NetworkEdge arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        adjustHeap(arr, size, i);

    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        adjustHeap(arr, i, 0);
    }
}

// Function to create and sort the array of edges
NetworkEdge* generateAndSortEdges(int **connections, int vertices, int &edgeCount) {
    NetworkEdge *edges = new NetworkEdge[vertices * (vertices - 1) / 2];
    edgeCount = 0;
    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {
            if (connections[i][j] != -1) {
                edges[edgeCount].start = i;
                edges[edgeCount].end = j;
                edges[edgeCount].weight = connections[i][j];
                edgeCount++;
            }
        }
    }
    heapSort(edges, edgeCount);
    return edges;
}

// Function to implement Kruskal's algorithm with adjacency matrix
void kruskalMinimumSpanningTree(int **connections, int vertices) {
    int edgeCount;
    NetworkEdge *edges = generateAndSortEdges(connections, vertices, edgeCount);

    int *parents = new int[vertices];
    for (int i = 0; i < vertices; ++i)
        parents[i] = i;

    NetworkEdge *result = new NetworkEdge[vertices - 1];
    int resultIndex = 0, edgeIndex = 0;
    int minCost = 0;

    while (resultIndex < vertices - 1 && edgeIndex < edgeCount) {
        NetworkEdge nextEdge = edges[edgeIndex++];

        int x = findRoot(parents, nextEdge.start);
        int y = findRoot(parents, nextEdge.end);

        if (x != y) {
            result[resultIndex++] = nextEdge;
            uniteSets(parents, x, y);
            minCost += nextEdge.weight;
        }
    }

    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < vertices - 1; ++i) {
        cout << result[i].start + 1 << "--" << result[i].end + 1 << " Weight: " << result[i].weight << endl;
    }

    cout << "Minimum Cost: " << minCost << endl;

    delete[] edges;
    delete[] parents;
    delete[] result;
}

// Function to create and populate the adjacency matrix
void acceptInputAndBuildAdjacencyMatrix(int **&connections, int vertices) {
    connections = new int*[vertices];
    for (int i = 0; i < vertices; ++i) {
        connections[i] = new int[vertices];
        for (int j = 0; j < vertices; ++j) {
            connections[i][j] = -1;
        }
    }

    int edges;
    cout << "Enter the number of edges: ";
    cin >> edges;

    if (edges > (vertices * (vertices - 1) / 2)) {
        cerr << "Error: The number of edges exceeds the maximum allowed for the given number of vertices." << endl;
        exit(1);
    }

    cout << "Enter edges in format (firstVertex secondVertex Weight), where vertices are between 1 and " << vertices << ":" << endl;
    for (int i = 0; i < edges; ++i) {
        int vertex1, vertex2, weight;
        cin >> vertex1 >> vertex2 >> weight;

        if (vertex1 < 1 || vertex1 > vertices || vertex2 < 1 || vertex2 > vertices) {
            cerr << "Error: Invalid vertex. Vertices must be between 1 and " << vertices << endl;
            exit(2);
        }

        if (vertex1 != vertex2) {
            connections[vertex1 - 1][vertex2 - 1] = weight;
            connections[vertex2 - 1][vertex1 - 1] = weight;
        }
    }
}

// Function to release memory allocated for the graph
void releaseGraph(int **&connections, int vertices) {
    for (int i = 0; i < vertices; ++i) {
        delete[] connections[i];
    }
    delete[] connections;
}

int main() {
    int vertices;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    int **connections = nullptr;

    acceptInputAndBuildAdjacencyMatrix(connections, vertices);

    kruskalMinimumSpanningTree(connections, vertices);

    releaseGraph(connections, vertices);

    return 0;
}
