// Write a C++ program to implement Kruskal's algorithm for a minimum spanning tree using a linked list approach.

#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
    Edge* next;
};

class Graph {
    int V;
    Edge* head;

public:
    Graph(int V) {
        this->V = V;
        head = NULL;
    }

    void addEdge(int s, int d, int w) {
        Edge* newEdge = new Edge;
        newEdge->src = s;
        newEdge->dest = d;
        newEdge->weight = w;
        newEdge->next = head;
        head = newEdge;
    }

    int find(int parent[], int i) {
        while(parent[i] != i)
            i = parent[i];
        return i;
    }

    void Union(int parent[], int x, int y) {
        int xset = find(parent, x);
        int yset = find(parent, y);
        parent[xset] = yset;
    }

    void kruskal() {
        Edge* edges[100];
        int count = 0;

        Edge* temp = head;
        while(temp != NULL) {
            edges[count++] = temp;
            temp = temp->next;
        }

        sort(edges, edges + count, [](Edge* a, Edge* b){
            return a->weight < b->weight;
        });

        int parent[V];
        for(int i = 0; i < V; i++)
            parent[i] = i;

        cout << "Edges in MST:\n";

        int edgeCount = 0;
        for(int i = 0; i < count && edgeCount < V-1; i++) {
            int x = find(parent, edges[i]->src);
            int y = find(parent, edges[i]->dest);

            if(x != y) {
                cout << edges[i]->src << " - " 
                     << edges[i]->dest 
                     << " : " << edges[i]->weight << endl;

                Union(parent, x, y);
                edgeCount++;
            }
        }
    }
};

int main() {
    Graph g(4);

    g.addEdge(0,1,10);
    g.addEdge(0,2,6);
    g.addEdge(0,3,5);
    g.addEdge(1,3,15);
    g.addEdge(2,3,4);

    g.kruskal();

    return 0;
}