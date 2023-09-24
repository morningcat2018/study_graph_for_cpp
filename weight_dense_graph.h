#ifndef WEIGHT_DENSE_GRAPH_HEAD
#define WEIGHT_DENSE_GRAPH_HEAD

#include <iostream>
#include <vector>
#include <cassert>
#include "edge.h"

using namespace std;

// 有权图 邻接矩阵
template <typename Weight>
class WeightDenseGraph
{
private:
    int vertices;                   // 点的数量
    int edges;                      // 边的数量
    bool directed;                  // 是否为有向图
    vector<vector<Edge<Weight> *> > g; // 否则编译器会误以为是 >>
public:
    WeightDenseGraph(int v, bool d) : vertices(v), directed(d)
    {
        this->edges = 0;
        // n * n 的矩阵
        for (int i = 0; i < vertices; i++)
        {
            vector<Edge<Weight> *> vec(vertices, NULL);
            g.push_back(vec);
            // g.push_back(vector<Edge<Weight>*>(vertices, NULL));
        }
    }
    ~WeightDenseGraph()
    {
        for (int i = 0; i < vertices; i++)
            for (int j = 0; j < vertices; j++)
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
        WeightDenseGraph &G;
        int v;
        int index;

    public:
        adjIterator(WeightDenseGraph &graph, int v);
        Edge<Weight> *begin();
        Edge<Weight> *next();
        bool end();
    };
};

template <typename Weight>
void WeightDenseGraph<Weight>::addEdge(int v1, int v2, Weight w)
{
    assert(v1 >= 0 && v1 < vertices);
    assert(v2 >= 0 && v2 < vertices);
    if (hasEdge(v1, v2))
    {
        delete g[v1][v2];
        if (!directed)
        {
            delete g[v2][v1];
        }
        edges--;
    }
    g[v1][v2] = new Edge<Weight>(v1, v2, w);
    if (!directed)
    {
        // 无向图
        g[v2][v1] = new Edge<Weight>(v2, v1, w);
    }
    edges++;
}

template <typename Weight>
bool WeightDenseGraph<Weight>::hasEdge(int v1, int v2)
{
    assert(v1 >= 0 && v1 < vertices);
    assert(v2 >= 0 && v2 < vertices);
    return g[v1][v2] != NULL;
}

template <typename Weight>
void WeightDenseGraph<Weight>::show()
{
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
            if (g[i][j] != NULL)
                cout << g[i][j]->getW() << "\t";
            else
                cout << "NULL"
                     << "\t";
        cout << endl;
    }
}

template <typename Weight>
WeightDenseGraph<Weight>::adjIterator::adjIterator(WeightDenseGraph &graph, int v) : G(graph)
{
    this->v = v;
    this->index = NULL;
}

template <typename Weight>
Edge<Weight> *WeightDenseGraph<Weight>::adjIterator::begin()
{
    index = -1;
    return next();
}

template <typename Weight>
Edge<Weight> *WeightDenseGraph<Weight>::adjIterator::next()
{
    for (index += 1; index < G.V(); index++)
        if (G.g[v][index] != NULL)
            return G.g[v][index];
    return NULL;
}

template <typename Weight>
bool WeightDenseGraph<Weight>::adjIterator::end()
{
    return index >= G.V();
}
#endif