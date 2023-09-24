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