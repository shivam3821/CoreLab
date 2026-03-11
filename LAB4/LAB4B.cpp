// Also find the total number of distinct paths between two nodes u and v.

#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    int countPathsUtil(int u, int v) {
        if (u == v)
            return 1;

        int count = 0;

        for (int i : adj[u])
            count += countPathsUtil(i, v);

        return count;
    }

    int countPaths(int u, int v) {
        return countPathsUtil(u, v);
    }
};

int main() {
    Graph g(5);

    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(2,3);
    g.addEdge(3,4);

    int u = 0, v = 4;

    cout << "Total distinct paths: " << g.countPaths(u,v);

    return 0;
}