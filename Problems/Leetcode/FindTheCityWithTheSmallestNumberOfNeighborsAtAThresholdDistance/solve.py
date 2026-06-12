class Solution:
    def findTheCity(self, n: int, edges: List[List[int]], threshold: int) -> int:
        INF = float('inf')

        graph = [[INF] * n for _ in range(n)]
        for u, v, d in edges:
            graph[u][v] = d
            graph[v][u] = d
        
        for i in range(n):
            graph[i][i] = 0
        
        for mid in range(n):
            for u in range(n):
                for v in range(n):
                    if graph[u][mid] != INF and graph[mid][v] != INF:
                        graph[u][v] = min(graph[u][v], graph[u][mid] + graph[mid][v])
        
        counter = defaultdict(int)
        min_freq = INF
        res = -1
        for u in range(n):
            for v in range(n):
                if v == u:
                    continue
                if graph[u][v] <= threshold:
                    counter[u] += 1
            
            if min_freq >= counter[u]:
                min_freq = counter[u]
                res = u
        
        return res