#include <bits/stdc++.h>
using namespace std;
/*
1. Write a program to find the shortest path between
    two vertices in a graph using Dijkstra's algorithm.
*/

// Adjacency list
struct Node
{
    int v;
    int w;
    Node *next;
};

//Graph class
class Graph
{
private:
    //Data memebers
    int V;
    vector<Node *> adj;

public:
    Graph(int vertex)
    {
        V = vertex;
        adj.resize(V + 1, nullptr); //1 based indexing
    }

    //Adding an edge
    void addEdge(int src, int dest, int weight)
    {
        //src to dest
        Node *tempSrcHead = adj[src];
        Node *newSrcNode = new Node{dest, weight};
        newSrcNode->next = tempSrcHead;
        adj[src] = newSrcNode;

        //dest to src
        Node *tempDestHead = adj[dest];
        Node *newDestNode = new Node{src, weight};
        newDestNode->next = tempDestHead;
        adj[dest] = newDestNode;
    }

    //display function
    void display()
    {
        for (int i = 1; i < V; i++)
        {
            cout << "Vertex " << i << " :";
            Node *tempNode = adj[i];
            while (tempNode)
            {
                cout << "{ " << tempNode->v << "," << tempNode->w << "}, ";
                tempNode = tempNode->next;
            }
            cout << endl;
        }
    }

    // dijkstra's algorithm function
    void DijkstrasAlgo(int src, int dest)
    {
        //min heap (priority queue)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        //display array
        vector<int> dist(V + 1, INT_MAX);
        dist[src] = 0;
        pq.emplace(0, src);

        //main loop
        while (!pq.empty())
        {   
            //vertex with smallest known distance
            auto topVal = pq.top();
            pq.pop();

            int currDist = topVal.first;
            int pqTopVertex = topVal.second;

            //skip outdated entries
            if (currDist > dist[pqTopVertex] || currDist < 0)
            {
                continue;
            }

            //relax adjacent edges
            Node *temp = adj[pqTopVertex];

            while (temp)
            {
                int vertex = temp->v;
                int weight = temp->w;

                if (dist[pqTopVertex] != INT_MAX)
                {
                    if ((dist[pqTopVertex] + weight) < dist[vertex])
                    {
                        dist[vertex] = dist[pqTopVertex] + weight;
                        pq.emplace(dist[vertex], vertex);
                    }
                }
                temp = temp->next;
            }

            //early stop
            if (pqTopVertex == dest)
            {
                break;
            }
        }

        //output result
        if (dist[dest] != INT_MAX)
        {
            cout << "\nFrom src: " << src << " to Dest: " << dest << " shortest distance is: " << dist[dest] << endl;
        }
        else
        {
            cout << "\nFrom src: " << src << " to Dest: " << dest << " no shortest path exist " << endl;
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

    g.DijkstrasAlgo(1, 3);

    return 0;
}