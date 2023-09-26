import queue


class SparseGraph(object):
    def __init__(self, v: int, directed=False):
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

    def add_edge(self, v1: int, v2: int):
        assert (0 <= v1 < self.vertices)
        assert (0 <= v2 < self.vertices)
        self.g[v1].append(v2)
        if not self.directed and v1 != v2:
            self.g[v2].append(v1)
        self.edges = self.edges + 1

    def has_edge(self, v1: int, v2: int):
        assert (0 <= v1 < self.vertices)
        assert (0 <= v2 < self.vertices)
        for i in self.g[v1]:
            if self.g[v1][i] == v2:
                return True
        return False

    def show(self):
        for i in range(self.vertices):
            print("vertex %d : %s" % (i, self.g[i]))

    def read_file(self, file_name: str):
        graph_data_file = open(file_name, 'r')
        first_line = graph_data_file.readline()
        lst = first_line.replace("\n", "").split(" ")
        v = int(lst[0])
        assert (v == self.vertices)
        lines = graph_data_file.readlines()
        for line in lines:
            lst = line.replace("\n", "").split(" ")
            self.add_edge(int(lst[0]), int(lst[1]))

    # 获取相邻的顶点
    def get_adjacent_v(self, v: int):
        assert (0 <= v < self.vertices)
        return self.g[v]


class Bfs(object):
    def __init__(self, graph: SparseGraph, v_start: int):
        self.g = graph
        assert (0 <= v_start < self.g.get_vertices())
        self.v_start = v_start
        self.visited = [False] * self.g.get_vertices()
        self.v_from = [-1] * self.g.get_vertices()
        self.ord = [-1] * self.g.get_vertices()
        q = queue.Queue()
        q.put(v_start)
        self.visited[v_start] = True
        self.ord[v_start] = 0
        while not q.empty():
            v_top = q.get()
            edges = self.g.get_adjacent_v(v_top)
            for e in edges:
                if not self.visited[e]:
                    q.put(e)
                    self.visited[e] = True
                    self.v_from[e] = v_top
                    self.ord[e] = self.ord[v_top] + 1

    def get_shortest_path(self, v_end: int):
        bfs_list = []
        p = v_end
        while p != -1:
            bfs_list.append(p)
            p = self.v_from[p]
        return list(reversed(bfs_list))
        # return bfs_list[::-1]


class Dfs(object):
    def __init__(self, graph: SparseGraph):
        self.g = graph
        self.visited = [False] * self.g.get_vertices()
        self.v_from = [-1] * self.g.get_vertices()
        self.v_id = [-1] * self.g.get_vertices()
        self.ccount = 0  # 连通分量
        for i in range(self.g.get_vertices()):
            if not self.visited[i]:
                self.dfs(i)
                self.ccount = self.ccount + 1

    def dfs(self, v: int):
        assert (0 <= v < self.g.get_vertices())
        self.visited[v] = True
        self.v_id[v] = self.ccount + 1
        edges = self.g.get_adjacent_v(v)
        for e in edges:
            if not self.visited[e]:
                self.v_from[e] = v
                self.dfs(e)

    # 校验两个顶点是否在一个连通里
    def is_connect(self, v1, v2):
        assert (0 <= v1 < self.g.get_vertices())
        assert (0 <= v2 < self.g.get_vertices())
        return self.v_id[v1] == self.v_id[v2]

    # 获取连通量
    def get_count(self):
        return self.ccount


# python3 sparse_graph.py
if __name__ == '__main__':
    sg = SparseGraph(13, False)
    sg.read_file("graph_data1.txt")
    # sg.show()
    bfs = Bfs(sg, 0)
    bfs_list = bfs.get_shortest_path(4)
    print(bfs_list)

    dfs = Dfs(sg)
    print(dfs.get_count())
