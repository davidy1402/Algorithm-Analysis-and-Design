#include <iostream>

using namespace std;

const int MAX_EDGES = 20; 
const int V = 6;       

struct Edge {
    int u;     
    int v;     
    int weight; 
};

int parentArray[V];

void make_sets() {
    for (int v = 0; v < V; v++) {
        parentArray[v] = v; 
    }
}

int find_set(int u) {
    while (parentArray[u] != u) {
        u = parentArray[u];
    }
    return u;
}

void union_sets(int u, int v) {
    int rootU = find_set(u);
    int rootV = find_set(v);
    if (rootU != rootV) {
        parentArray[rootU] = rootV; 
    }
}

void Kruskal(Edge edges[], int edgeCount) {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = i + 1; j < edgeCount; j++) {
            if (edges[i].weight > edges[j].weight) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    make_sets();

    Edge ET[V - 1]; 
    int ecounter = 0;
    
    int k = 0;

    while (ecounter < V - 1 && k < edgeCount) {
        Edge current_edge = edges[k];
        k++;

        int u = current_edge.u;
        int v = current_edge.v;

        if (find_set(u) != find_set(v)) {
            ET[ecounter] = current_edge;
            
            ecounter++;
            
            union_sets(u, v);
        }
    }

    cout << "Edges composing the Minimum Spanning Tree (Kruskal):\n";
    cout << "Edge \tWeight\n";
    for (int i = 0; i < ecounter; i++) {
        cout << ET[i].u << " - " << ET[i].v << " \t" << ET[i].weight << "\n";
    }
}

int main() {
    Edge edges[MAX_EDGES] = {
        {0, 1, 4},
        {0, 2, 0},
        {0, 3, 0},
        {0, 4, 0},
        {0, 5, 0},
        {1, 2, 8},
        {1, 3, 0},
        {1, 4, 0},
        {1, 5, 0},
        {2, 3, 7},
        {2, 4, 0},
        {2, 5, 4},
        {3, 4, 9},
        {3, 5, 14},
        {4, 5, 10}
    };

    int edgeCount = 15; 

    Kruskal(edges, edgeCount);

    return 0;
}