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