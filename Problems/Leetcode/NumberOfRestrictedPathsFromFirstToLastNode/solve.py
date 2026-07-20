from typing import List
import heapq

class Solution:
    def countRestrictedPaths(self, n: int, edges: List[List[int]]) -> int:
        MOD = 10**9 + 7
        
        # 1. Build the adjacency list
        graph = [[] for _ in range(n + 1)]
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))
            
        # 2. Run Dijkstra's algorithm from node n to find distanceToLastNode
        dist = [float('inf')] * (n + 1)
        dist[n] = 0
        min_heap = [(0, n)] # (distance, node)
        
        while min_heap:
            d, u = heapq.heappop(min_heap)
            
            if d > dist[u]:
                continue
                
            for v, w in graph[u]:
                if dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w
                    heapq.heappush(min_heap, (dist[v], v))
                    
        # 3. Dynamic Programming with Memoization to count restricted paths
        memo = {}
        
        def dfs(node):
            if node == n:
                return 1
            if node in memo:
                return memo[node]
            
            paths = 0
            for neighbor, _ in graph[node]:
                # Move to neighbor only if its distance to n is strictly smaller
                if dist[node] > dist[neighbor]:
                    paths = (paths + dfs(neighbor)) % MOD
                    
            memo[node] = paths
            return paths
            
        return dfs(1)
