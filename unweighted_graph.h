#ifndef UNWEIGHTED_GRAPH_HEAD
#define UNWEIGHTED_GRAPH_HEAD

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class UnweightedGraph
{
private:
    int vertices;          // 点的数量
    int edges;             // 边的数量
    bool directed;         // 是否为有向图
    vector<vector<int> > g; // 编译器会误以为是 >>
public:
    UnweightedGraph(int v, bool d) : vertices(v), directed(d)
    {
        this->edges = 0;
        for (int i = 0; i < vertices; i++)
            g.push_back(vector<int>()); // 初始化每个顶点的邻接点
    }
    ~UnweightedGraph() {}
    int V() { return vertices; }
    int E() { return edges; }
    void addEdge(int v1, int v2);
    bool hasEdge(int v1, int v2);
    void show();
    void buildByFile(const string &file_name);
    void bfs(const int v_start, vector<int> &vec);

    class adjIterator
    {
    private:
        UnweightedGraph &G;
        int v;
        int index;

    public:
        adjIterator(UnweightedGraph &graph, int v);
        int begin();
        int next();
        bool end();
    };
};

void UnweightedGraph::addEdge(int v1, int v2)
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

bool UnweightedGraph::hasEdge(int v1, int v2)
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

void UnweightedGraph::show()
{
    for (int i = 0; i < vertices; i++)
    {
        cout << "vertex" << i << ":\t";
        for (int j = 0; j < g[i].size(); j++)
            cout << g[i][j] << "\t";
        cout << endl;
    }
}

void UnweightedGraph::buildByFile(const string &file_name)
{
    ifstream file(file_name);
    string line;
    int V, E;
    assert(file.is_open());
    assert(getline(file, line));
    stringstream ss(line);
    ss >> V >> E;
    assert(V == vertices);
    for (int i = 0; i < E; i++)
    {
        assert(getline(file, line));
        stringstream ss(line);
        int v1, v2;
        ss >> v1 >> v2;
        assert(v1 >= 0 && v1 < V);
        assert(v2 >= 0 && v2 < V);
        addEdge(v1, v2);
    }
}

void UnweightedGraph::bfs(const int v_start, vector<int> &vec)
{
    assert(v_start >= 0 && v_start < vertices);
    bool *visited = new bool[vertices];
    int *from = new int[vertices];
    int *ord = new int[vertices];
    for (int i = 0; i < vertices; i++)
    {
        visited[i] = false;
        from[i] = -1;
        ord[i] = -1;
    }
    vec.push_back(v_start);

    // 广度优先遍历
    queue<int> q;
    q.push(v_start);
    visited[v_start] = true;
    ord[v_start] = 0;
    while (!q.empty())
    {
        int v_top = q.front();
        q.pop();

        adjIterator adj(*this, v_top);
        for (int i = adj.begin(); !adj.end(); i = adj.next())
        {
            if (!visited[i])
            {
                vec.push_back(i);
                q.push(i);
                visited[i] = true;
                from[i] = v_top; // 记录来源 : i 是从 v_top 的遍历而来
                ord[i] = ord[v_top] + 1;
            }
        }
    }
}

UnweightedGraph::adjIterator::adjIterator(UnweightedGraph &graph, int v) : G(graph)
{
    this->index = 0;
    this->v = v;
}

int UnweightedGraph::adjIterator::begin()
{
    index = 0;
    if (G.g[v].size())
        return G.g[v][index];
    return -1;
}

int UnweightedGraph::adjIterator::next()
{
    index++;
    if (index < G.g[v].size())
        return G.g[v][index];
    return -1;
}

bool UnweightedGraph::adjIterator::end()
{
    return index >= G.g[v].size();
}
#endif