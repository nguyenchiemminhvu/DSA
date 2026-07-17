from typing import List
from collections import defaultdict
import heapq

class Solution:
    def countPaths(self, n: int, roads: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v, w in roads:
            graph[u].append((w, v))
            graph[v].append((w, u))
        
        # st = set([0])
        # min_cost = 0xFFFFFFFF
        # res = 0
        # def dfs(cur: int, cost: int):
        #     nonlocal min_cost, res
        #     if cur == n - 1:
        #         if min_cost > cost:
        #             res = 1
        #             min_cost = cost
        #         elif min_cost == cost:
        #             res += 1
        #         return
        #     for w, adj in graph[cur]:
        #         if adj not in st:
        #             st.add(adj)
        #             dfs(adj, cost + w)
        #             st.remove(adj)
        # dfs(0, 0)
        # return res

        mod = 10**9 + 7
        INF = float('inf')
        dist = [INF] * n
        dist[0] = 0
        ways = [0] * n
        ways[0] = 1

        pq = [(0, 0)] # (cost, node)
        while pq:
            cur_cost, cur_node = heapq.heappop(pq)
            if cur_cost > dist[cur_node]:
                continue

            for cost, adj_node in graph[cur_node]:
                next_cost = cur_cost + cost
                if next_cost < dist[adj_node]:
                    dist[adj_node] = next_cost
                    ways[adj_node] = ways[cur_node] % mod
                    heapq.heappush(pq, (next_cost, adj_node))
                elif next_cost == dist[adj_node]:
                    ways[adj_node] = (ways[adj_node] + ways[cur_node]) % mod
        
        return ways[n - 1] % mod