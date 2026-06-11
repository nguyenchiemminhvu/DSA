from collections import defaultdict
from typing import List

class Solution:
    def maximalPathQuality(self, values: List[int], edges: List[List[int]], maxTime: int) -> int:
        n = len(values)
        adj = defaultdict(list)
        for u, v, t in edges:
            adj[u].append((t, v))
            adj[v].append((t, u))
        
        max_path = 0
        def backtracking(cur_node: int, remain_time: int, temp: List[int]):
            nonlocal max_path
            if remain_time < 0:
                return
            
            if cur_node == 0:
                max_path = max(max_path, sum(values[i] for i in set(temp)))

            for time, next_node in adj[cur_node]:
                temp.append(next_node)
                backtracking(next_node, remain_time - time, temp)
                temp.pop()
        
        backtracking(0, maxTime, [0])
        return max_path