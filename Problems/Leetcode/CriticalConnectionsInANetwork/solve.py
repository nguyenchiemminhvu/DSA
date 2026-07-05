from collections import defaultdict

class graph_analyzer:
    def __init__(self, n: int):
        self.n = n
        self.graph = defaultdict(list)
    
    def add_edge(self, u: int, v: int):
        self.graph[u].append(v)
        self.graph[v].append(u)
    
    def find_critical_edge(self) -> list[list[int]]:
        res = []

        timestamp = 0
        discover_time = [-1] * self.n
        low_link = [-1] * self.n
        def dfs(node: int, parent: int):
            nonlocal timestamp
            discover_time[node] = timestamp
            low_link[node] = timestamp
            timestamp += 1
            for adj in self.graph[node]:
                if adj == parent:
                    continue
                
                if discover_time[adj] != -1:
                    low_link[node] = min(low_link[node], discover_time[adj])
                else:
                    dfs(adj, node)
                    low_link[node] = min(low_link[node], low_link[adj])
                    if low_link[adj] > discover_time[node]:
                        res.append([node, adj])
        
        for node in range(self.n):
            if discover_time[node] == -1:
                dfs(node, -1)
        return res

class Solution:
    def criticalConnections(self, n: int, connections: List[List[int]]) -> List[List[int]]:
        graph = graph_analyzer(n)
        for u, v in connections:
            graph.add_edge(u, v)
        
        return graph.find_critical_edge()