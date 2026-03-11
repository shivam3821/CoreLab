// Write a C++ program to find the longest path from a given source in a DAG using an adjacency list. 
// Also find the total number of distinct paths between two nodes u and v.

#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int,int>>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& st) {
        visited[v] = true;

        for (auto i : adj[v]) {
            if (!visited[i.first])
                topologicalSortUtil(i.first, visited, st);
        }

        st.push(v);
    }

    void longestPath(int src) {
        stack<int> st;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
            if (!visited[i])
                topologicalSortUtil(i, visited, st);

        vector<int> dist(V, INT_MIN);
        dist[src] = 0;

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            if (dist[u] != INT_MIN) {
                for (auto i : adj[u]) {
                    int v = i.first;
                    int weight = i.second;

                    if (dist[v] < dist[u] + weight)
                        dist[v] = dist[u] + weight;
                }
            }
        }

        cout << "Longest distances from source:\n";
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MIN)
                cout << "INF ";
            else
                cout << dist[i] << " ";
        }
    }
};

int main() {
    Graph g(6);

    g.addEdge(0,1,5);
    g.addEdge(0,2,3);
    g.addEdge(1,3,6);
    g.addEdge(1,2,2);
    g.addEdge(2,4,4);
    g.addEdge(2,5,2);
    g.addEdge(2,3,7);
    g.addEdge(3,5,1);
    g.addEdge(3,4,-1);
    g.addEdge(4,5,-2);

    g.longestPath(1);

    return 0;
}