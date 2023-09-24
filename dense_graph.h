#ifndef DENSE_GRAPH_HEAD
#define DENSE_GRAPH_HEAD

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 邻接矩阵(Adjacency Matrix)
class DenseGraph
{
private:
    int vertices;           // 点的数量
    int edges;              // 边的数量
    bool directed;          // 是否为有向图
    vector<vector<bool> > g; // 邻接矩阵 注意:这里的两个 > 不要连在一起,否则编译器会误以为是 >>
public:
    DenseGraph(int v, bool d) : vertices(v), directed(d)
    {
        this->edges = 0;
        // n * n 的矩阵
        for (int i = 0; i < vertices; i++)
            g.push_back(vector<bool>(vertices, false));
    }
    ~DenseGraph() {}
    int V() { return vertices; }
    int E() { return edges; }
    void addEdge(int v1, int v2);
    bool hasEdge(int v1, int v2);
    void show();

    // 迭代器
    class adjIterator
    {
    private:
        DenseGraph &G;
        int v;
        int index;

    public:
        adjIterator(DenseGraph &graph, int v);
        int begin();
        int next();
        bool end();
    };
};

void DenseGraph::addEdge(int v1, int v2)
{
    assert(v1 >= 0 && v1 < vertices);
    assert(v2 >= 0 && v2 < vertices);
    if (hasEdge(v1, v2))
    {
        return;
    }
    g[v1][v2] = true;
    if (!directed)
    {
        // 无向图
        g[v2][v1] = true;
    }
    edges++;
}

bool DenseGraph::hasEdge(int v1, int v2)
{
    assert(v1 >= 0 && v1 < vertices);
    assert(v2 >= 0 && v2 < vertices);
    return g[v1][v2];
}

void DenseGraph::show()
{
    cout << "节点格式:" << endl;
    for (int i = 0; i < vertices; i++)
    {
        cout << "vertex" << i << ":\t";
        for (int j = 0; j < g[i].size(); j++)
            if (g[i][j])
                cout << j << "\t";
        cout << endl;
    }
    cout << "矩阵格式:" << endl;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
            cout << g[i][j] << "\t";
        cout << endl;
    }
}

DenseGraph::adjIterator::adjIterator(DenseGraph &graph, int v) : G(graph)
{
    this->v = v;
    this->index = -1;
}

int DenseGraph::adjIterator::begin()
{
    index = -1;
    return next();
}

int DenseGraph::adjIterator::next()
{
    for (index += 1; index < G.V(); index++)
        if (G.g[v][index])
            return index;
    return -1;
}

bool DenseGraph::adjIterator::end()
{
    return index >= G.V();
}
#endif