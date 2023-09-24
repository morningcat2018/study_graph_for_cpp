#include <iostream>
#include "sparse_graph.h"
#include "dense_graph.h"
#include "read_graph.h"
#include "graph_dfs.h"
#include "path.h"
#include "shortest_path.h"

#include "weight_dense_graph.h"
#include "weight_sparse_graph.h"
#include "weight_read_graph.h"


using namespace std;

void testcase1()
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
}

void testcase2()
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
}

void testcase3()
{
    string file_name = "graph_data1.txt";
    SparseGraph sg(13, false);
    ReadGraph<SparseGraph> readGraph(sg, file_name);
    sg.show();
    cout << "---" << endl;

    DenseGraph dg(13, false);
    ReadGraph<DenseGraph> readGraph2(dg, file_name);
    dg.show();
}

void testcase4()
{
    string file_name = "graph_data1.txt";
    SparseGraph sg(13, false);
    ReadGraph<SparseGraph> readGraph(sg, file_name);
    GraphDfs<SparseGraph> dfs(sg);
    // dfs.dfs(0); // 从节点0开始进行深度优先遍历
    cout << "连通分量:" << dfs.count() << endl;
    cout << dfs.isConnect(7, 8) << endl;
}

void testcase5()
{
    string file_name = "graph_data2.txt";
    SparseGraph sg(7, false);
    ReadGraph<SparseGraph> readGraph(sg, file_name);

    // 寻找节点0到节点6的路径
    Path<SparseGraph> p(sg, 0);
    p.showPath(6);

    // 广度优先算法寻找无权图的最短路径
    ShortestPath<SparseGraph> sp(sg, 0);
    sp.showPath(4);
}

void testcase11()
{
    int V = 8;
    cout << fixed << setprecision(2);
    string file_name = "graph_data3.txt";
    WeightDenseGraph<double> wdg(8, false);
    WeightReadGraph<WeightDenseGraph<double>, double> readGraph(wdg, file_name);
    wdg.show();
}

void testcase12()
{
    int V = 8;
    cout << fixed << setprecision(2);
    string file_name = "graph_data3.txt";
    WeightSparseGraph<double> wsg(8, false);
    WeightReadGraph<WeightSparseGraph<double>, double> readGraph(wsg, file_name);
    wsg.show();
}

// g++ main.cpp && ./a.out
// g++ main.cpp -o maincpp.out && ./maincpp.out
int main()
{
    testcase12();
    return 0;
}