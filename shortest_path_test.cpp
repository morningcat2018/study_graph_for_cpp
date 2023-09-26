#include "sparse_graph.h"
#include "dense_graph.h"
#include "read_graph.h"
#include "path.h"
#include "shortest_path.h"

// g++ shortest_path_test.cpp && ./a.out
int main()
{
    string file_name = "graph_data2.txt";
    SparseGraph sg(7, false);
    ReadGraph<SparseGraph> readGraph(sg, file_name);

    // 寻找节点0到节点6的路径
    Path<SparseGraph> path(sg, 0);
    path.showPath(6);

    // 广度优先算法寻找无权图的最短路径
    ShortestPath<SparseGraph> shortestPath(sg, 0);
    shortestPath.showPath(4);
    return 0;
}