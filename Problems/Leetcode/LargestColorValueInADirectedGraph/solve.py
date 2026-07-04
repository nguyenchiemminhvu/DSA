from collections import deque
from typing import List
import string

class Solution:
    def largestPathValue(self, colors: str, edges: List[List[int]]) -> int:
        ctoi = {c: i for i, c in enumerate(string.ascii_lowercase)}
        
        n = len(colors)
        graph = {
            i: [] for i in range(n)
        }

        in_degree = [0] * n
        for u, v in edges:
            graph[u].append(v)
            in_degree[v] += 1
        
        dp = [[0] * 26 for _ in range(n)] # dp[node][color]
        q = deque()
        for i in range(n):
            if in_degree[i] == 0:
                q.append(i)
                dp[i][ctoi[colors[i]]] = 1
        
        max_freq = 1
        count_topo = 0
        while q:
            cur = q.popleft()
            count_topo += 1

            for adj in graph[cur]:
                # update dp to next node
                for i in range(26):
                    dp[adj][i] = max(dp[cur][i], dp[adj][i])

                in_degree[adj] -= 1
                if in_degree[adj] == 0:
                    q.append(adj)
                    dp[adj][ctoi[colors[adj]]] += 1
                    max_freq = max(max_freq, dp[adj][ctoi[colors[adj]]])
        
        if count_topo != n:
            return -1
        
        return max_freq