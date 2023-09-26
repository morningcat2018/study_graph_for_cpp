#include "sparse_graph.h"
#include "dense_graph.h"
#include "read_graph.h"

// g++ read_graph_test.cpp && ./a.out
int main()
{
    string file_name = "graph_data1.txt";
    SparseGraph sg(13, false);
    ReadGraph<SparseGraph> readGraph(sg, file_name);
    sg.show();
    cout << "---" << endl;

    DenseGraph dg(13, false);
    ReadGraph<DenseGraph> readGraph2(dg, file_name);
    dg.show();
    return 0;
}