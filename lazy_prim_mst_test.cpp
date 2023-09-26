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