#ifndef WEIGHT_GRAPH_EDGE_HEAD
#define WEIGHT_GRAPH_EDGE_HEAD

#include <iostream>
#include <cassert>

using namespace std;

// 模板类
template <typename Weight>
class Edge
{
private:
    int from, to; // 边的两个顶点
    Weight w;     // 权重
public:
    Edge() {}
    Edge(int from, int to, Weight w) : from(from), to(to), w(w) {}
    ~Edge() {}
    int getFrom() { return from; }
    int getTo() { return to; }
    Weight getW() { return w; }
    // 获取边的另一个顶点
    int getOtherV(int v)
    {
        assert(v == from || v == to);
        return v == from ? to : from;
    }
    // 操作符的重载
    friend ostream &operator<<(ostream &os, const Edge &e)
    {
        os << e.from << "-" << e.to << ":" << e.w;
        return os;
    }
    bool operator<(Edge<Weight> &other_e) { return w < other_e.getW(); }
    bool operator<=(Edge<Weight> &other_e) { return w <= other_e.getW(); }
    bool operator>(Edge<Weight> &other_e) { return w > other_e.getW(); }
    bool operator>=(Edge<Weight> &other_e) { return w >= other_e.getW(); }
    bool operator==(Edge<Weight> &other_e) { return w == other_e.getW(); }
};

#endif