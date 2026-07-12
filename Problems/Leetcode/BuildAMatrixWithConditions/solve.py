from collections import defaultdict, deque
from typing import List

class Solution:
    def buildMatrix(self, k: int, row_conds: List[List[int]], col_conds: List[List[int]]) -> List[List[int]]:
        def topo_sort_bfs(conds: List[List[int]]) -> List[int]:
            graph = defaultdict(list)
            in_degree = [0] * (k + 1)
            for u, v in conds:
                graph[u].append(v)
                in_degree[v] += 1
            topo = []
            q = deque([u for u in range(1, k + 1) if in_degree[u] == 0])
            while q:
                cur = q.popleft()
                topo.append(cur)
                for adj in graph[cur]:
                    in_degree[adj] -= 1
                    if in_degree[adj] == 0:
                        q.append(adj)
            return topo if len(topo) == k else []

        row_topo = topo_sort_bfs(row_conds)
        col_topo = topo_sort_bfs(col_conds)
        if not row_topo or not col_topo:
            return []
        
        row_pos = {num: i for i, num in enumerate(row_topo)}
        col_pos = {num: i for i, num in enumerate(col_topo)}

        res = [[0] * k for _ in range(k)]
        for i in range(1, k + 1):
            res[row_pos[i]][col_pos[i]] = i
        return res