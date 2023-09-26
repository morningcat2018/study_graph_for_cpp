#include "sparse_graph.h"
#include "dense_graph.h"
#include "read_graph.h"
#include "graph_dfs.h"

// g++ graph_dfs_test.cpp && ./a.out
int main()
{
    string file_name = "graph_data1.txt";
    SparseGraph sg(13, false);
    ReadGraph<SparseGraph> readGraph(sg, file_name);
    GraphDfs<SparseGraph> dfs(sg);
    // dfs.dfs(0); // 从节点0开始进行深度优先遍历
    cout << "连通分量:" << dfs.count() << endl;
    cout << dfs.isConnect(7, 8) << endl;
    return 0;
}