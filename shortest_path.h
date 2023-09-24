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