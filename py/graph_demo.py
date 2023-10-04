# 案例代码来自《算法图解》
from collections import deque

graph = {}
graph["you"] = ["alice", "bob", "claire"]
graph["bob"] = ["anuj", "peggy"]
graph["alice"] = ["peggy"]
graph["claire"] = ["thom", "jonny"]
graph["anuj"] = []
graph["peggy"] = []
graph["thom"] = []
graph["jonny"] = []


# 使用队列对图进行广度优先遍历
def bfs_search(name):
    search_queue = deque()
    search_queue += graph[name]
    searched = []  # 已搜索过的元素
    while search_queue:
        person = search_queue.popleft()  # 取出队列中第一个元素
        if person not in searched:  # 过滤已搜索过的元素
            if person_is_seller(person):
                print("%s is a mango seller" % person)
                return True
            else:
                searched.append(person)
                search_queue += graph[person]  # 将person的朋友加入队列
    return False


def person_is_seller(name):
    return name[-1] == 'm'


# python3 py/graph_demo.py
if __name__ == '__main__':
    bfs_search("you")
