#include <iostream>
#include <climits>

using namespace std;

const int V = 6; 

void Prim(int graph[V][V], int startVertex) {
    int parent[V]; 
    for(int i = 0; i < V; i++) parent[i] = -1;

    bool inVT[V];
    for(int i = 0; i < V; i++) inVT[i] = false;

    inVT[startVertex] = true;
    

    for (int i = 1; i <= V - 1; i++) {
        int minWeight = INT_MAX;
        int v_star = -1; 
        int u_star = -1; 

        for (int v = 0; v < V; v++) {
            if (inVT[v]) { 
                for (int u = 0; u < V; u++) {
                    if (!inVT[u] && graph[v][u] != 0) { 
                        if (graph[v][u] < minWeight) {
                            minWeight = graph[v][u];
                            v_star = v;
                            u_star = u;
                        }
                    }
                }
            }
        }

  
        if (v_star != -1 && u_star != -1) {
            // VT <- VT U {u*}
            inVT[u_star] = true;
            
            // ET <- ET U {e*}
            parent[u_star] = v_star; 
        }
    }

    cout << "Edges composing the Minimum Spanning Tree (Prim):\n";
    cout << "Edge \tWeight\n";
    for (int i = 0; i < V; i++) {
        if (i != startVertex && parent[i] != -1) {
            cout << parent[i] << " - " << i << " \t" << graph[parent[i]][i] << "\n";
        }
    }
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    int startVertex = 0; 
    Prim(graph, startVertex);

    return 0;
}