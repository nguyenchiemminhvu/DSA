from collections import defaultdict
from typing import List
import heapq

class Solution:
    def maxProbability(self, n: int, edges: List[List[int]], probs: List[float], start_node: int, end_node: int) -> float:
        graph = defaultdict(list)
        for i in range(len(edges)):
            u, v = edges[i]
            p = probs[i]
            graph[u].append((-p, v))
            graph[v].append((-p, u))

        dp = [0.0] * n
        dp[start_node] = 1.0

        pq = [(-1.0, start_node)]
        while pq:
            cur_p, u = heapq.heappop(pq)
            cur_p *= -1.0
            if cur_p < dp[u]:
                continue

            for p, v in graph[u]:
                if dp[v] < cur_p * -p:
                    dp[v] = cur_p * -p
                    heapq.heappush(pq, (-dp[v], v))
        
        return dp[end_node]