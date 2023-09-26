#include "dense_graph.h"

// g++ dense_graph_test.cpp && ./a.out
int main()
{
    int V = 20;
    int E = 100;
    srand(time(NULL));

    DenseGraph dg(V, false);
    for (int i = 0; i < E; i++)
    {
        int a = rand() % V;
        int b = rand() % V;
        dg.addEdge(a, b);
    }

    for (int v = 0; v < V; v++)
    {
        cout << v << " : ";
        DenseGraph::adjIterator adj(dg, v);
        for (int w = adj.begin(); !adj.end(); w = adj.next())
            cout << w << " ";
        cout << endl;
    }
    return 0;
}