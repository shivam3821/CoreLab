/*
Lab 3. Formulate and implement Dijkstra’s algorithm to compute
    the shortest path between two vertices in a weighted graph
    with non-negative edge weights. Provide a time complexity
    analysis of the implementation.
*/
#include <bits/stdc++.h>
using namespace std;

//Adjacency List Node
struct Node
{
    int vertex;
    int weight;
    Node *next;
};

//Graph class 
class Graph
{
private:
    int V;
    vector<Node *> adj; // adjacency list using linked lists

public:
    Graph(int v)
    {
        V = v;
        adj.resize(V + 1, nullptr); // 1-based indexing
    }

    // add weighted edge
    void addEdge(int src, int dest, int weight)
    {
        Node *tempSrcHead = adj[src];
        Node *newSrcNode = new Node{dest, weight};
        newSrcNode->next = tempSrcHead;
        adj[src] = newSrcNode;

        Node *tempDestHead = adj[dest];
        Node *newDestNode = new Node{src, weight};
        newDestNode->next = tempDestHead;
        adj[dest] = newDestNode;
    }

    //display function
    void display()
    {
        for (int i = 1; i <= V; i++)
        {
            cout << "Vertex " << i << " :";
            Node *tempNode = adj[i];
            while (tempNode)
            {
                cout << "{ " << tempNode->vertex << "," << tempNode->weight << "}, ";
                tempNode = tempNode->next;
            }
            cout << endl;
        }
    }

    //dijkstra's algorithm
    void dijkstra(int src)
    {
        vector<int> dist(V + 1, INT_MAX);
        //min priority queue
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>>
            pq;

        //distance array
        dist[src] = 0;
        pq.push({0, src}); //push source: start exploring from source

        while (!pq.empty()) //main loop
        {
            auto topVal = pq.top();
            pq.pop();

            int currDist = topVal.first;
            int u = topVal.second;

            if (currDist > dist[u]) //skip outdated entries
                continue;

            // find sortest path : relaxation
            Node *temp = adj[u];
            while (temp)
            {
                int v = temp->vertex;
                int wt = temp->weight;

                if (dist[u] + wt < dist[v])
                {
                    dist[v] = dist[u] + wt;
                    pq.push({dist[v], v});
                }
                temp = temp->next;
            }
        }

        // Print distances
        cout << "Shortest distances from source " << src << ":\n";
        for (int i = 1; i <= V; i++)
        {
            if (dist[i] == INT_MAX)
                cout << i << " : INF\n";
            else
                cout << i << " : " << dist[i] << "\n";
        }
    }
};

//Main function
int main()
{
    Graph g(5);

    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 8);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 5, 6);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 10);
    g.display();
    cout << "\n\n";

    g.dijkstra(1);

    return 0;
}
