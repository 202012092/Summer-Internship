#include <iostream>
#include <vector>

using namespace std;

class Graph {

public:

    void addEdge(vector<int> adj[], const int& u, const int& v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void printGraph(vector<int> adj[], const int& V)
    {
        for (int v = 0; v < V; ++v)
        {
            cout << "\n Adjacency list of vertex "
                << v << "\n head ";
            for (auto x : adj[v])
                cout << "-> " << x;
            printf("\n");
        }
    }
};

int main()
{
    const int V = 5;

    vector<int> adj[V];

    Graph g;

    g.addEdge(adj, 0, 1);
    g.addEdge(adj, 0, 4);
    g.addEdge(adj, 1, 2);
    g.addEdge(adj, 1, 3);
    g.addEdge(adj, 1, 4);
    g.addEdge(adj, 2, 3);
    g.addEdge(adj, 3, 4);
    g.printGraph(adj, V);
    return 0;
}