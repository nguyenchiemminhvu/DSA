from collections import defaultdict
from typing import List

class Solution:
    def weightedSum(self, parent: list[int], nums: list[int]) -> int:
        graph = defaultdict(list)
        for u, p in enumerate(parent):
            graph[p].append(u)

        def height(node: int) -> int:
            h = 1
            for adj in graph[node]:
                h = max(h, 1 + height(adj))
            return h

        h = height(0)

        def dfs(node: int, d: int) -> int:
            nonlocal h
            val = nums[node] * (h - d + 1)
            for adj in graph[node]:
                val += dfs(adj, d + 1)
            return val
        
        return dfs(0, 1)