#ifndef LAZY_PRIM_MST_H
#define LAZY_PRIM_MST_H

#include <vector>
#include <cassert>
#include "edge.h"
#include "min_heap.h"


// 使用Prim算法求图的 最小生成树(mst)
template <typename Graph, typename Weight>
class LazyPrimMST
{
private:
    Graph &G;                       // 图的引用
    MinHeap<Edge<Weight> > min_heap; // 最小堆, 算法辅助数据结构
    bool *marked;                   // 标记数组, 在算法运行过程中标记节点i是否被访问
    vector<Edge<Weight> > mst;       // 最小生成树所包含的所有边
    Weight mstWeight;               // 最小生成树的权值
    void visit(int v);

public:
    // 构造函数,
    LazyPrimMST(Graph &graph);
    // 析构函数
    ~LazyPrimMST()
    {
        delete[] marked;
    }
    // 返回最小生成树的所有边
    vector<Edge<Weight> > mstEdges()
    {
        return mst;
    };
    // 返回最小生成树的权值
    Weight result()
    {
        return mstWeight;
    };
};

// 访问节点v
template <typename Graph, typename Weight>
void LazyPrimMST<Graph, Weight>::visit(int v)
{
    assert(!marked[v]);
    marked[v] = true;
    // 将和节点v相连接的所有未访问的边放入最小堆中
    typename Graph::adjIterator adj(G, v);
    for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
        if (!marked[e->getOtherV(v)])
            min_heap.insert(*e);
}

template <typename Graph, typename Weight>
LazyPrimMST<Graph, Weight>::LazyPrimMST(Graph &graph) : G(graph), min_heap(MinHeap<Edge<Weight> >(graph.E()))
{
    marked = new bool[G.V()];
    for (int i = 0; i < G.V(); i++)
        marked[i] = false;
    mst.clear();

    // Lazy Prim
    visit(0);
    while (!min_heap.isEmpty())
    {
        Edge<Weight> e = min_heap.extractMin();       // 使用最小堆找出已经访问的边中权值最小的边
        if (marked[e.getFrom()] == marked[e.getTo()]) // 如果这条边的两端都已经访问过了, 则扔掉这条边
            continue;
        mst.push_back(e);         // 否则, 这条边则应该存在在最小生成树中
        if (!marked[e.getFrom()]) // 访问和这条边连接的还没有被访问过的节点
            visit(e.getFrom());
        else
            visit(e.getTo());
    }

    // 计算最小生成树的权值
    mstWeight = mst[0].getW();
    for (int i = 1; i < mst.size(); i++)
        mstWeight += mst[i].getW();
}

#endif // LAZY_PRIM_MST_H