#ifndef SPARSE_GRAPH_HEAD
#define SPARSE_GRAPH_HEAD

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 邻接表
class SparseGraph
{
private:
    int vertices;          // 点的数量
    int edges;             // 边的数量
    bool directed;         // 是否为有向图
    vector< vector<int> > g; // 邻接表 注意:这里的两个 > 不要连在一起,否则编译器会误以为是 >>
public:
    SparseGraph(int v, bool d) : vertices(v), directed(d)
    {
        this->edges = 0;
        for (int i = 0; i < vertices; i++)
            g.push_back(vector<int>()); // 初始化每个顶点的邻接点
    }
    ~SparseGraph() {}
    int V() { return vertices; }
    int E() { return edges; }
    void addEdge(int v1, int v2);
    bool hasEdge(int v1, int v2);
    void show();

    // 迭代器
    class adjIterator
    {
    private:
        SparseGraph &G;
        int v;
        int index;

    public:
        adjIterator(SparseGraph &graph, int v);
        int begin();
        int next();
        bool end();
    };
};

void SparseGraph::addEdge(int v1, int v2)
{
    assert(v1 >= 0 && v1 < vertices);
    assert(v2 >= 0 && v2 < vertices);
    // 关于平行边,可以在图构建完成后进行统一处理
    // if (hasEdge(v1, v2))
    //     return;
    g[v1].push_back(v2);
    if (!directed && v1 != v2)
    {
        g[v2].push_back(v1);
    }
    edges++;
}

bool SparseGraph::hasEdge(int v1, int v2)
{
    assert(v1 >= 0 && v1 < vertices);
    assert(v2 >= 0 && v2 < vertices);
    for (int i = 0; i < g[v1].size(); i++)
    {
        if (g[v1][i] == v2)
            return true;
    }
    return false;
}

void SparseGraph::show()
{
    for (int i = 0; i < vertices; i++)
    {
        cout << "vertex" << i << ":\t";
        for (int j = 0; j < g[i].size(); j++)
            cout << g[i][j] << "\t";
        cout << endl;
    }
}

SparseGraph::adjIterator::adjIterator(SparseGraph &graph, int v) : G(graph)
{
    this->index = 0;
    this->v = v;
}

int SparseGraph::adjIterator::begin()
{
    index = 0;
    if (G.g[v].size())
        return G.g[v][index];
    return -1;
}

int SparseGraph::adjIterator::next()
{
    index++;
    if (index < G.g[v].size())
        return G.g[v][index];
    return -1;
}

bool SparseGraph::adjIterator::end()
{
    return index >= G.g[v].size();
}
#endif