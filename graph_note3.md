图论 C++实现 笔记3-最小生成树


- [# BiliBili 图啊图](https://www.bilibili.com/video/BV1Pf4y1s7u1/)
- [# Github 代码](https://github.com/morningcat2018/study_graph_for_cpp)


## 最小生成树 Minimum Span Tree


![image.png](https://p1-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/abc078cdf0d7490d8da0812bd0cf5714~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1046&h=850&s=354888&e=png&b=fdfdfd)

应用场景
- 电缆布线
- 网络布线

注意点:最小生成树主要是针对`有权无向的连通图`而言的

## 切分定理

把图中的节点分为两个部分,称为一个`切分`.


![image.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/dd173fa9184b434e9d79db2a750e868e~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1122&h=856&s=349605&e=png&b=fcfcfc)


如果一个边的两个顶点属于切分的不同部分,这个边称为`横切边`.


![image.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/d0538d9e6c0b4a458237b5237c70bfd0~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1174&h=830&s=393374&e=png&b=fdfdfd)


切分定理:给定任意切分,横切边中权值最小的边必然属于最小生成树.


![image.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/fcde58e611b84e07a98960e3d9a7597b~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=2044&h=808&s=544236&e=png&b=fdfdfd)


![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/c4251b23fb114a4280c0e8ec5631add6~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1126&h=850&s=374595&e=png&b=fdfdfd)

## Lazy Prim

![image.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/48e0dcbf922e464fba31228e0ad8123a~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1920&h=824&s=605213&e=png&b=fdfdfd)


![image.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/59eb076c90c04e61b4499f06dfc7e4ac~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1902&h=796&s=648070&e=png&b=fdfdfd)


![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/68416bde6f244c3ea4aff7e1a7f2f862~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1948&h=818&s=679934&e=png&b=fefefe)


![image.png](https://p1-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/46f4f5040aa84abca6ff67e1a3f8f7bb~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1964&h=1020&s=771610&e=png&b=fefefe)


![image.png](https://p9-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/838f7b83b99244a3b5b4cd4b35d57a58~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1922&h=810&s=705969&e=png&b=fefefe)


![image.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/5df8693d52ba4bd3ad62a5aaba66a44f~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1918&h=818&s=717814&e=png&b=fefefe)


![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/abfc8e264ab54e68abdcb2b81564c320~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1958&h=820&s=719704&e=png&b=fefefe)


![image.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/442b34b61552427f8719f208e7104899~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1932&h=834&s=660407&e=png&b=fefefe)


min_heap.h

```cpp
//
// Created by liuyubobobo on 9/13/16.
// https://github.com/liuyubobobo/Play-with-Algorithms/blob/master/08-Minimum-Span-Trees/Course%20Code%20(C%2B%2B)/03-Lazy-Prim/MinHeap.h
//

#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <algorithm>
#include <cassert>

using namespace std;

// 最小堆
template<typename Item>
class MinHeap{

private:
    Item *data;
    int count;
    int capacity;

    void shiftUp(int k){
        while( k > 1 && data[k/2] > data[k] ){
            swap( data[k/2], data[k] );
            k /= 2;
        }
    }

    void shiftDown(int k){
        while( 2*k <= count ){
            int j = 2*k;
            if( j+1 <= count && data[j+1] < data[j] ) j ++;
            if( data[k] <= data[j] ) break;
            swap( data[k] , data[j] );
            k = j;
        }
    }

public:

    // 构造函数, 构造一个空堆, 可容纳capacity个元素
    MinHeap(int capacity){
        data = new Item[capacity+1];
        count = 0;
        this->capacity = capacity;
    }

    // 构造函数, 通过一个给定数组创建一个最小堆
    // 该构造堆的过程, 时间复杂度为O(n)
    MinHeap(Item arr[], int n){
        data = new Item[n+1];
        capacity = n;

        for( int i = 0 ; i < n ; i ++ )
            data[i+1] = arr[i];
        count = n;

        for( int i = count/2 ; i >= 1 ; i -- )
            shiftDown(i);
    }

    ~MinHeap(){
        delete[] data;
    }

    // 返回堆中的元素个数
    int size(){
        return count;
    }

    // 返回一个布尔值, 表示堆中是否为空
    bool isEmpty(){
        return count == 0;
    }

    // 向最小堆中插入一个新的元素 item
    void insert(Item item){
        assert( count + 1 <= capacity );
        data[count+1] = item;
        shiftUp(count+1);
        count ++;
    }

    // 从最小堆中取出堆顶元素, 即堆中所存储的最小数据
    Item extractMin(){
        assert( count > 0 );
        Item ret = data[1];
        swap( data[1] , data[count] );
        count --;
        shiftDown(1);
        return ret;
    }

    // 获取最小堆中的堆顶元素
    Item getMin(){
        assert( count > 0 );
        return data[1];
    }
};

#endif //MIN_HEAP_H
```

lazy_prim_mst.h

```cpp
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
```

lazy_prim_mst_test.cpp

```cpp
#include "weight_dense_graph.h"
#include "weight_sparse_graph.h"
#include "weight_read_graph.h"
#include "lazy_prim_mst.h"

// g++ lazy_prim_mst_test.cpp && ./a.out
int main(){
    int V = 8;
    string file_name = "graph_data4.txt";
    WeightSparseGraph<double> wsg(8, false);
    WeightReadGraph<WeightSparseGraph<double>, double> readGraph(wsg, file_name);
    // wsg.show();

    cout<<"Test Lazy Prim MST:"<<endl;
    LazyPrimMST<WeightSparseGraph<double>, double> lazyPrimMST(wsg);
    vector<Edge<double> > mst = lazyPrimMST.mstEdges();
    for( int i = 0 ; i < mst.size() ; i ++ )
        cout<<mst[i]<<endl;
    cout<<"The MST weight is: "<<lazyPrimMST.result()<<endl;
    cout<<endl;

    return 0;
}
```