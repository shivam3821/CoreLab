// Implement a solution for the Travelling Salesman Problem using a circular linked list and compute the minimum route cost using a heuristic approach.

#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int city;
    Node* next;
};

Node* insert(Node* head, int city) {
    Node* newNode = new Node;
    newNode->city = city;

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        return head;
    }

    Node* temp = head;
    while (temp->next != head)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = head;

    return head;
}

void display(Node* head) {
    Node* temp = head;
    do {
        cout << temp->city << " -> ";
        temp = temp->next;
    } while (temp != head);
    cout << head->city << endl;
}

int main() {

    int n = 4;

    int cost[4][4] = {
        {0,10,15,20},
        {10,0,35,25},
        {15,35,0,30},
        {20,25,30,0}
    };

    bool visited[4] = {false};

    Node* tour = NULL;

    int current = 0;
    visited[current] = true;

    tour = insert(tour, current);

    int totalCost = 0;

    for (int i = 0; i < n-1; i++) {

        int nearest = -1;
        int minCost = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && cost[current][j] < minCost) {
                minCost = cost[current][j];
                nearest = j;
            }
        }

        visited[nearest] = true;
        tour = insert(tour, nearest);

        totalCost += minCost;
        current = nearest;
    }

    totalCost += cost[current][0];

    cout << "Tour (Circular Linked List):\n";
    display(tour);

    cout << "Minimum Route Cost (Heuristic): " << totalCost;

    return 0;
}