#include "weight_dense_graph.h"
#include "weight_sparse_graph.h"
#include "weight_read_graph.h"
#include "prim_mst.h"

// g++ prim_mst_test.cpp && ./a.out
int main(){
    int V = 8;
    string file_name = "graph_data4.txt";
    WeightSparseGraph<double> wsg(8, false);
    WeightReadGraph<WeightSparseGraph<double>, double> readGraph(wsg, file_name);

    cout<<"Test Lazy Prim MST:"<<endl;
    PrimMST<WeightSparseGraph<double>, double> primMST(wsg);
    vector<Edge<double> > mst = primMST.mstEdges();
    for( int i = 0 ; i < mst.size() ; i ++ )
        cout<<mst[i]<<endl;
    cout<<"The MST weight is: "<<primMST.result()<<endl;
    cout<<endl;

    return 0;
}