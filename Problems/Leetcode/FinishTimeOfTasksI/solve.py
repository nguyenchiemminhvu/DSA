from collections import defaultdict
from typing import List

class Solution:
    def finishTime(self, n: int, edges: List[List[int]], base: List[int]) -> int:
        INF = float('inf')
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
        
        finished_time = [INF] * n

        def dfs(task: int):
            if not graph[task]:
                finished_time[task] = base[task]
                return
            
            mi = INF
            ma = 0
            for adj in graph[task]:
                dfs(adj)
                t = finished_time[adj]
                mi = min(mi, t)
                ma = max(ma, t)
            own_duration = (ma - mi) + base[task]
            finished_time[task] = ma + own_duration
        
        dfs(0)
        return finished_time[0]