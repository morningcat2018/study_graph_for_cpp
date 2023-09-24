[# 图啊图](https://www.bilibili.com/video/BV1Pf4y1s7u1/)

## 邻接表

![image.png](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/ab704e605462434c8b01fcee20f68d2e~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1880&h=988&s=404857&e=png&b=ffffff)

邻接表适合表示`稀疏图`(Sparse Graph)

## 邻接矩阵

![image.png](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/26e0a57d1bb142a6be7c504e3ad15d78~tplv-k3u1fbpfcp-jj-mark:0:0:0:0:q75.image#?w=1752&h=1030&s=472696&e=png&b=fefefe)

邻接矩阵适合表示`稠密图`(Dense Graph)

- 个人理解,稠密图中需要每个点都与图中的其他所有点的大部分都相连,才能称为稠密图
- 即使一个图,点很多,铺开也很大,但每个点都只与身边几个点相连,也只是稀疏图
- `完全图`比较适合使用邻接矩阵来表示

## 邻接矩阵 C++的一种实现方式

dense_graph.h 头文件

```cpp
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
```


```cpp
// 测试用例
#include "dense_graph.h"

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
```

## 邻接表 C++的一种实现方式

sparse_graph.h

```cpp
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
```


```cpp
// 测试用例
#include "sparse_graph.h"
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
```

## 读取文件构建图

read_graph.h 头文件

```cpp
#ifndef READ_GRAPH_HEAD
#define READ_GRAPH_HEAD

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

// 模板类
template <typename Graph>
class ReadGraph
{
public:
    ReadGraph(Graph &g, const string &file_name)
    {
        // 文件输入流
        ifstream file(file_name);
        string line;
        int V, E;

        // 检验文件是否打开成功
        assert(file.is_open());
        // 获取文件内容的第一行
        assert(getline(file, line));

        // 将字符串转换成字符流
        stringstream ss(line);
        // 解析字符流
        ss >> V >> E;

        assert(V == g.V());

        for (int i = 0; i < E; i++)
        {
            assert(getline(file, line));
            stringstream ss(line);
            int v1, v2;
            ss >> v1 >> v2;
            assert(v1 >= 0 && v1 < V);
            assert(v2 >= 0 && v2 < V);
            g.addEdge(v1, v2);
        }
    }
};

#endif
```

graph_data1.txt 文件内容

```txt
13 13
0 5
4 3
0 1
9 12
6 4
5 4
0 2
11 12
9 10
0 6
7 8
9 11
5 3
```

测试用例

```cpp
#include <iostream>
#include "sparse_graph.h"
#include "dense_graph.h"
#include "read_graph.h"

using namespace std;

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

int main()
{
    testcase3();
    return 0;
}
```

## 图的深度优先遍历

graph_dfs.h

```cpp
#ifndef GRAPH_DFS_HEAD
#define GRAPH_DFS_HEAD

#include <iostream>
#include <cassert>

using namespace std;

// 模板类
template <typename Graph>
class GraphDfs
{
private:
    Graph &G;
    bool *visited;
    int *id;
    int ccount; // 连通分量

public:
    GraphDfs(Graph &graph) : G(graph)
    {
        visited = new bool[G.V()];
        id = new int[G.V()];
        ccount = 0;
        for (int i = 0; i < G.V(); i++)
        {
            visited[i] = false;
            id[i] = -1;
        }
        for (int i = 0; i < G.V(); i++)
        {
            if (!visited[i])
            {
                dfs(i);
                cout << endl;
                ccount++;
            }
        }
    }
    ~GraphDfs()
    {
        delete[] visited;
        delete[] id;
    }
    void dfs(int v);
    int count() { return ccount; }
    bool isConnect(int v1, int v2)
    {
        assert(v1 >= 0 && v1 < G.V());
        assert(v2 >= 0 && v2 < G.V());
        return id[v1] == id[v2];
    }
};

template <typename Graph>
void GraphDfs<Graph>::dfs(int v)
{
    cout << v << "\t";
    visited[v] = true;
    id[v] = ccount + 1;
    typename Graph::adjIterator adj(G, v);
    for (int i = adj.begin(); !adj.end(); i = adj.next())
    {
        if (!visited[i])
            dfs(i);
    }
}

#endif
```

测试用例

```cpp
#include <iostream>
#include "sparse_graph.h"
#include "dense_graph.h"
#include "read_graph.h"
#include "graph_dfs.h"

using namespace std;

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

int main()
{
    testcase4();
    return 0;
}
```

## 图的深度优先遍历的寻路

path.h

```cpp
#ifndef GRAPH_PATH_HEAD
#define GRAPH_PATH_HEAD

#include <iostream>
#include <cassert>
#include <vector>
#include <stack>

using namespace std;

// 模板类
template <typename Graph>
class Path
{
private:
    Graph &G;
    int v_start;
    bool *visited;
    int *from;
    // 遍历v的相邻节点
    void dfs(int v)
    {
        visited[v] = true;
        typename Graph::adjIterator adj(G, v);
        for (int i = adj.begin(); !adj.end(); i = adj.next())
        {
            if (!visited[i])
            {
                from[i] = v;
                dfs(i);
            }
        }
    }

public:
    Path(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        visited = new bool[G.V()];
        from = new int[G.V()];
        for (int i = 0; i < G.V(); i++)
        {
            visited[i] = false;
            from[i] = -1;
        }
        this->v_start = s;

        // 寻路
        dfs(s);
    }
    ~Path()
    {
        delete[] visited;
        delete[] from;
    }
    bool hasPath(int v);
    void path(int v, vector<int> &vec);
    void showPath(int v);
};

template <typename Graph>
bool Path<Graph>::hasPath(int v)
{
    assert(v >= 0 && v < G.V());
    return visited[v];
}

template <typename Graph>
void Path<Graph>::path(int v, vector<int> &vec)
{
    assert(v >= 0 && v < G.V());
    stack<int> s;
    int p = v;
    while (p != -1)
    {
        s.push(p);
        p = from[p];
    }

    //
    vec.clear();
    while (!s.empty())
    {
        vec.push_back(s.top());
        s.pop();
    }
}

template <typename Graph>
void Path<Graph>::showPath(int v)
{
    assert(v >= 0 && v < G.V());
    vector<int> vec;
    path(v, vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i];
        if (i == vec.size() - 1)
            cout << endl;
        else
            cout << " -> ";
    }
}
#endif
```

graph_data2.txt

```txt
7 8
0 1
0 2
0 5
0 6
3 4
3 5
4 5
4 6
```

测试用例

```cpp
#include <iostream>
#include "sparse_graph.h"
#include "dense_graph.h"
#include "read_graph.h"
#include "path.h"

using namespace std;

void testcase5()
{
    string file_name = "graph_data2.txt";
    SparseGraph sg(7, false);
    ReadGraph<SparseGraph> readGraph(sg, file_name);

    // 寻找节点0到节点6的路径
    Path<SparseGraph> p(sg, 0);
    p.showPath(6);
}

int main()
{
    testcase5();
    return 0;
}
```

## 图的深度优先遍历的时间复杂度

邻接表 O(V+E)

邻接矩阵 O(V^2)

## 图的广度优先遍历

`广度优先遍历`可以得到`无权图`的`最短路径`

shortest_path.h

```cpp
#ifndef GRAPH_SHORTEST_PATH_HEAD
#define GRAPH_SHORTEST_PATH_HEAD

#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// 模板类
template <typename Graph>
class ShortestPath
{
private:
    Graph &G;
    int v_start; //     起始点
    bool *visited;
    int *from; //
    int *ord;  // 距离起始点的距离
public:
    ShortestPath(Graph &graph, int s) : G(graph)
    {
        assert(s >= 0 && s < G.V());
        visited = new bool[G.V()];
        from = new int[G.V()];
        ord = new int[G.V()];
        for (int i = 0; i < G.V(); i++)
        {
            visited[i] = false;
            from[i] = -1;
            ord[i] = -1;
        }
        this->v_start = s;

        // 无向图最短路径
        queue<int> q;
        // 广度优先遍历
        q.push(s);
        visited[s] = true;
        ord[s] = 0;
        while (!q.empty())
        {
            int v_top = q.front();
            q.pop();

            typename Graph::adjIterator adj(G, v_top);
            for (int i = adj.begin(); !adj.end(); i = adj.next())
            {
                if (!visited[i])
                {
                    q.push(i);
                    visited[i] = true;
                    from[i] = v_top; // 记录来源 : i 是从 v_top 的遍历而来
                    ord[i] = ord[v_top] + 1;
                }
            }
        }
    }
    ~ShortestPath()
    {
        delete[] visited;
        delete[] from;
        delete[] ord;
    }
    bool hasPath(int v);
    void path(int v, vector<int> &vec);
    void showPath(int v);
    int length(int v);
};

template <typename Graph>
bool ShortestPath<Graph>::hasPath(int v)
{
    assert(v >= 0 && v < G.V());
    return visited[v];
}

template <typename Graph>
int ShortestPath<Graph>::length(int v)
{
    assert(v >= 0 && v < G.V());
    return ord[v];
}

template <typename Graph>
void ShortestPath<Graph>::path(int v, vector<int> &vec)
{
    assert(v >= 0 && v < G.V());
    stack<int> s;
    int p = v;
    while (p != -1)
    {
        s.push(p);
        p = from[p];
    }

    //
    vec.clear();
    while (!s.empty())
    {
        vec.push_back(s.top());
        s.pop();
    }
}

template <typename Graph>
void ShortestPath<Graph>::showPath(int v)
{
    assert(v >= 0 && v < G.V());
    vector<int> vec;
    path(v, vec);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i];
        if (i == vec.size() - 1)
            cout << endl;
        else
            cout << " -> ";
    }
}
#endif
```

测试用例

```cpp
#include <iostream>
#include "sparse_graph.h"
#include "dense_graph.h"
#include "read_graph.h"
#include "graph_dfs.h"
#include "path.h"
#include "shortest_path.h"

using namespace std;

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
    sp.showPath(6);
}

int main()
{
    testcase5();
    return 0;
}
```




