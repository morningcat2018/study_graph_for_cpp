#ifndef WEIGHT_SPARSE_GRAPH_HEAD
#define WEIGHT_SPARSE_GRAPH_HEAD

#include <iostream>
#include <vector>
#include <cassert>
#include "edge.h"

using namespace std;

// 有权图 邻接表
template <typename Weight>
class WeightSparseGraph
{
private:
    int vertices;                     // 点的数量
    int edges;                        // 边的数量
    bool directed;                    // 是否为有向图
    vector<vector<Edge<Weight> *> > g; // 否则编译器会误以为是 >>
public:
    WeightSparseGraph(int v, bool d) : vertices(v), directed(d)
    {
        this->edges = 0;
        for (int i = 0; i < vertices; i++)
            g.push_back(vector<Edge<Weight> *>()); // 初始化每个顶点的邻接点
    }
    ~WeightSparseGraph()
    {
        for (int i = 0; i < vertices; i++)
            for (int j = 0; j < g[i].size(); j++)
                if (g[i][j] != NULL)
                    delete (g[i][j]);
    }
    int V() { return vertices; }
    int E() { return edges; }
    void addEdge(int v1, int v2, Weight w);
    bool hasEdge(int v1, int v2);
    void show();

    // 迭代器
    class adjIterator
    {
    private:
        WeightSparseGraph &G;
        int v;
        int index;

    public:
        adjIterator(WeightSparseGraph &graph, int v);
        Edge<Weight> *begin();
        Edge<Weight> *next();
        bool end();
    };
};

template <typename Weight>
void WeightSparseGraph<Weight>::addEdge(int v1, int v2, Weight w)
{
    assert(v1 >= 0 && v1 < vertices);
    assert(v2 >= 0 && v2 < vertices);
    // 稀疏图不处理平行边问题
    g[v1].push_back(new Edge<Weight>(v1, v2, w));
    if (!directed && v1 != v2)
        g[v2].push_back(new Edge<Weight>(v2, v1, w));
    edges++;
}

template <typename Weight>
bool WeightSparseGraph<Weight>::hasEdge(int v1, int v2)
{
    assert(v1 >= 0 && v1 < vertices);
    assert(v2 >= 0 && v2 < vertices);
    for (int i = 0; i < g[v1].size(); i++)
    {
        if (g[v1][i]->getOtherV() == v2)
            return true;
    }
    return false;
}

template <typename Weight>
void WeightSparseGraph<Weight>::show()
{
    for (int i = 0; i < vertices; i++)
    {
        cout << "vertex" << i << ":\t";
        for (int j = 0; j < g[i].size(); j++)
            cout << "( to:" << g[i][j]->getTo() << ", weight:" << g[i][j]->getW() << " )\t";
        cout << endl;
    }
}

template <typename Weight>
WeightSparseGraph<Weight>::adjIterator::adjIterator(WeightSparseGraph<Weight> &graph, int v) : G(graph)
{
    this->index = 0;
    this->v = v;
}

template <typename Weight>
Edge<Weight> *WeightSparseGraph<Weight>::adjIterator::begin()
{
    index = 0;
    if (G.g[v].size())
        return G.g[v][index];
    return NULL;
}

template <typename Weight>
Edge<Weight> *WeightSparseGraph<Weight>::adjIterator::next()
{
    index++;
    if (index < G.g[v].size())
        return G.g[v][index];
    return NULL;
}

template <typename Weight>
bool WeightSparseGraph<Weight>::adjIterator::end()
{
    return index >= G.g[v].size();
}
#endif