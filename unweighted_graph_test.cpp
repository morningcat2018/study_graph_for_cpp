#include "unweighted_graph.h"

// g++ unweighted_graph_test.cpp && ./a.out
int main()
{
    int V = 13;
    string file_name = "graph_data1.txt";

    UnweightedGraph graph(V, false);
    graph.buildByFile(file_name);
    vector<int> vec;
    graph.bfs(0, vec);
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;
    return 0;
}