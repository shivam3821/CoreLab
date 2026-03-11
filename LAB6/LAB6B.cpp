// Write a C++ program to find the Maximum Matching in a Bipartite Graph using the Hungarian Algorithm .

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool bpm(int u, vector<vector<int>>& graph, bool seen[], int matchR[], int n) {

    for (int v = 0; v < n; v++) {

        if (graph[u][v] && !seen[v]) {

            seen[v] = true;

            if (matchR[v] < 0 || bpm(matchR[v], graph, seen, matchR, n)) {
                matchR[v] = u;
                return true;
            }
        }
    }

    return false;
}

int maxMatching(vector<vector<int>>& graph, int m, int n) {

    int matchR[n];
    memset(matchR, -1, sizeof(matchR));

    int result = 0;

    for (int u = 0; u < m; u++) {

        bool seen[n];
        memset(seen, 0, sizeof(seen));

        if (bpm(u, graph, seen, matchR, n))
            result++;
    }

    return result;
}

int main() {

    vector<vector<int>> graph = {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,1,1},
        {1,0,0,1}
    };

    int m = 4;
    int n = 4;

    cout << "Maximum Matching = "
         << maxMatching(graph, m, n);

    return 0;
}