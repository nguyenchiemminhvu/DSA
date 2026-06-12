from typing import List

class Graph:
    INF = float('inf')

    def __init__(self, n: int, edges: List[List[int]]):
        self.n = n
        self.graph = [[Graph.INF] * n for _ in range(n)]
        for i in range(n):
            self.graph[i][i] = 0
        for u, v, d in edges:
            self.graph[u][v] = d
        
        for mid in range(n):
            for u in range(n):
                for v in range(n):
                    if self.graph[u][mid] != Graph.INF and self.graph[mid][v] != Graph.INF:
                        self.graph[u][v] = min(self.graph[u][v], self.graph[u][mid] + self.graph[mid][v])

    def addEdge(self, edge: List[int]) -> None:
        u, v, d = edge
        if d >= self.graph[u][v]:
            return
        
        self.graph[u][v] = d
        for i in range(self.n):
            for j in range(self.n):
                if self.graph[i][u] != Graph.INF and self.graph[v][j] != Graph.INF:
                    self.graph[i][j] = min(self.graph[i][j], self.graph[i][u] + d + self.graph[v][j])

    def shortestPath(self, node1: int, node2: int) -> int:
        d = self.graph[node1][node2]
        return -1 if d == Graph.INF else d


# Your Graph object will be instantiated and called as such:
# obj = Graph(n, edges)
# obj.addEdge(edge)
# param_2 = obj.shortestPath(node1,node2)