[# 图啊图](https://www.bilibili.com/video/BV1Pf4y1s7u1/)

## 邻接表

![image.png](pic/adjacency_matrix.png)

邻接表适合表示`稀疏图`(Sparse Graph)

## 邻接矩阵

![image.png](pic/adjacency_lists.png)

邻接矩阵适合表示`稠密图`(Dense Graph)

- 个人理解,稠密图中需要每个点都与图中的其他所有点的大部分都相连,才能称为稠密图
- 即使一个图,点很多,铺开也很大,但每个点都只与身边几个点相连,也只是稀疏图
- `完全图`比较适合使用邻接矩阵来表示

![image.png](pic/sparse_graph.png)

![image.png](pic/dense_graph.png)

## 邻接矩阵 C++的一种实现方式

dense_graph.h 

## 邻接表 C++的一种实现方式

sparse_graph.h

## 读取文件构建图

read_graph.h 

## 图的深度优先遍历

graph_dfs.h

## 图的深度优先遍历的寻路

path.h


## 图的深度优先遍历的时间复杂度

邻接表 O(V+E)

邻接矩阵 O(V^2)

## 图的广度优先遍历

`广度优先遍历`可以得到`无权图`的`最短路径`

shortest_path.h



