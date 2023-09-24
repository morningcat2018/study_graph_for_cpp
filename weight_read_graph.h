#ifndef WEIGTH_READ_GRAPH_HEAD
#define WEIGTH_READ_GRAPH_HEAD

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include "edge.h"

using namespace std;

template <typename Graph, typename Weight>
class WeightReadGraph
{
public:
    WeightReadGraph(Graph &g, const string &file_name)
    {
        ifstream file(file_name);
        string line;
        int V, E;
        assert(file.is_open());
        assert(getline(file, line));
        stringstream ss(line);
        ss >> V >> E;
        assert(V == g.V());
        for (int i = 0; i < E; i++)
        {
            assert(getline(file, line));
            stringstream ss(line);
            int v1, v2;
            Weight w;
            ss >> v1 >> v2 >> w;
            assert(v1 >= 0 && v1 < V);
            assert(v2 >= 0 && v2 < V);
            g.addEdge(v1, v2, w);
        }
    }
};

#endif