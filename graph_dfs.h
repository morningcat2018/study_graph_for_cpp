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