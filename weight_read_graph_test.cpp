#include "weight_dense_graph.h"
#include "weight_sparse_graph.h"
#include "weight_read_graph.h"

using namespace std;

// g++ weight_read_graph_test.cpp && ./a.out
int main()
{
    int V = 8;
    cout << fixed << setprecision(2);
    string file_name = "graph_data3.txt";
    WeightDenseGraph<double> wdg(8, false);
    WeightReadGraph<WeightDenseGraph<double>, double> readGraph1(wdg, file_name);
    wdg.show();

    WeightSparseGraph<double> wsg(8, false);
    WeightReadGraph<WeightSparseGraph<double>, double> readGraph2(wsg, file_name);
    wsg.show();
    return 0;
}