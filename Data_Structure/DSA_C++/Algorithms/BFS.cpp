#include <iostream>
#include <queue>

using namespace std;

void performBFS(int startNode, int numNodes, int adjMatrix[10][10]) {
    bool visited[10] = {false};
    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);
    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";
        for (int neighbor = 0; neighbor < numNodes; neighbor++) {

            if (adjMatrix[neighbor][current] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    int nodes = 5;
    int graph[10][10] = {{0, 1, 0, 0, 1},
                         {1, 0, 1, 0, 1},
                         {0, 1, 0, 1, 1},
                         {0, 0, 1, 0, 1},
                         {1, 1, 1, 1, 0}};

    performBFS(0, nodes, graph);

    return 0;
}
