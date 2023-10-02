from typing import Any
from edge import Edge

class WeightSparseGraph(object):
    def __init__(self, v: int, directed:bool=False):
        self.vertices = v
        self.edges = 0
        self.directed = directed
        self.g = {}
        for i in range(self.vertices):
            self.g[i] = []

    def get_vertices(self):
        return self.vertices

    def get_edges(self):
        return self.edges

    def add_edge(self, v1: int, v2: int, weight:Any):
        assert (0 <= v1 < self.vertices)
        assert (0 <= v2 < self.vertices)
        v_to = Edge(v1,v2,weight)
        self.g[v1].append(v_to)
        if not self.directed and v1 != v2:
            v_from = Edge(v2,v1,weight)
            self.g[v2].append(v_from)
        self.edges = self.edges + 1

    def has_edge(self, v1: int, v2: int):
        assert (0 <= v1 < self.vertices)
        assert (0 <= v2 < self.vertices)
        for i in self.g[v1]:
            if self.g[v1][i] == v2:
                return True
        return False
    
    def has_edge(self, v1:int,  v2:int):
        assert (0 <= v1 < self.vertices)
        assert (0 <= v2 < self.vertices)
        for e in self.g[v1]:
            if e.getOtherV() == v2:
                return True
        return False
    
    def show(self):
        for i in range(self.vertices):
            print("vertex%d :"%(i))
            for e in self.g[i]:
                print("(to:%s,weight:%s)"%(e.get_to(),e.get_weight()))
    
    def read_file(self, file_name: str):
        graph_data_file = open(file_name, 'r')
        first_line = graph_data_file.readline()
        lst = first_line.replace("\n", "").split(" ")
        v = int(lst[0])
        assert (v == self.vertices)
        lines = graph_data_file.readlines()
        for line in lines:
            lst = line.replace("\n", "").split(" ")
            self.add_edge(int(lst[0]), int(lst[1]),float(lst[2]))

# python3 py/weight_sparse_graph.py
if __name__ == '__main__':
    wsg = WeightSparseGraph(8, False)
    wsg.read_file("graph_data4.txt")
    wsg.show()
