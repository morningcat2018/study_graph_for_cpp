
#include "sparse_graph.h"

// g++ sparse_graph_test.cpp && ./a.out
int main()
{
    int V = 20;
    int E = 100;
    srand(time(NULL));

    SparseGraph sg(V, false);
    for (int i = 0; i < E; i++)
    {
        int a = rand() % V;
        int b = rand() % V;
        sg.addEdge(a, b);
    }

    for (int v = 0; v < V; v++)
    {
        cout << v << " : ";
        SparseGraph::adjIterator adj(sg, v);
        for (int w = adj.begin(); !adj.end(); w = adj.next())
            cout << w << " ";
        cout << endl;
    }
    return 0;
}