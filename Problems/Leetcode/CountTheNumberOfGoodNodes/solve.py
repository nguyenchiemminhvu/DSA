from collections import defaultdict
from typing import List

class Solution:
    def countGoodNodes(self, edges: List[List[int]]) -> int:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        res = 0
        def dfs(node, parent):
            nonlocal res
            if not graph[node]:
                return 0
            
            total = 1
            arr = []
            for adj in graph[node]:
                if adj == parent:
                    continue
                count = dfs(adj, node)
                total += count
                arr.append(count)
            
            if not arr or all(val == arr[0] for val in arr):
                res += 1
            
            return total

        dfs(0, -1)
        return res