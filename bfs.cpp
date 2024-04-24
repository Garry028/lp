#include <iostream>
#include <omp.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph
{
private:
    int numVertices;
    vector<vector<int>> adj;

public:
    Graph(int vertices) : numVertices(vertices), adj(numVertices) {}

    void addEdge(int src, int dest)
    {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }
    void viewGraph()
    {
        cout << "Graph: " << endl;
        for (int i = 0; i < numVertices; i++)
        {
            cout << "Vertices: " << i << " ";
            for (int neighbour : adj[i])
            {
                cout << neighbour << " ";
            }

            cout << endl;
        }
    }
    void bfs(int startVertex)
    {
        vector<bool> visited(numVertices, false);
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            cout << current << " ";
#pragma omp parallel for
            for (int neighbour : adj[current])
            {
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }
};

int main()
{
    int numVertices;
    cout << "Enter the number of vertices in graph: ";
    cin >> numVertices;

    Graph graph(numVertices);

    int numEdges;
    cout << "Enter the number of edges in the graph:";
    cin >> numEdges;

    cout << "Enter the edges  source and destination:\n";
    for (int i = 0; i < numEdges; i++)
    {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }
    graph.viewGraph();

    int startVertex;

    cout << "Enter starting vertext for BFS: ";
    cin >> startVertex;

    cout << "BFS is: ";
    graph.bfs(startVertex);
    cout << endl;
    return 0;
}

// Here's a sample input :
// vertices = 6, edges = 7, edges = ["0 1", "0 2", "1 2", "1 3", "2 3", "3 4", "4 5"], starting vertex = 0