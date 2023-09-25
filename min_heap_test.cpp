#include <iostream>
#include "min_heap.h"

using namespace std;

template <typename T>
void heapSortUsingMinHeap(T arr[], int n)
{
    MinHeap<T> minheap = MinHeap<T>(n);
    for (int i = 0; i < n; i++)
        minheap.insert(arr[i]);

    for (int i = 0; i < n; i++)
        arr[i] = minheap.extractMin();
}

// g++ min_heap_test.cpp && ./a.out
int main()
{
    int V = 7;
    MinHeap<int> minheap(V);
    minheap.insert(23);
    minheap.insert(87);
    minheap.insert(7);
    minheap.insert(64);
    minheap.insert(12);
    minheap.insert(9);
    minheap.insert(69);

    cout << minheap.extractMin() << endl;
    cout << minheap.extractMin() << endl;
    cout << minheap.extractMin() << endl;

    // 另一种方式
    const int N = 5;
    int arr[N] = {134, 78, 45, 90, 84};
    heapSortUsingMinHeap(arr, N);
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}