from collections import defaultdict
from typing import List

class Solution:
    def minEdgeReversals(self, n: int, edges: List[List[int]]) -> List[int]:
        adj = defaultdict(list)
        for u, v in edges:
            adj[u].append((v, 0))
            adj[v].append((u, 1))
        
        res = [0] * n
        
        def dfs_init(root, parent):
            rev_count = 0
            for next_node, weight in adj[root]:
                if next_node == parent:
                    continue
                rev_count += weight + dfs_init(next_node, root)
            return rev_count
        
        res[0] = dfs_init(0, -1)

        def dfs_reroot(root, parent):
            for next_node, weight in adj[root]:
                if next_node == parent:
                    continue
                
                if weight == 0:
                    res[next_node] = res[root] + 1
                else:
                    res[next_node] = res[root] - 1
                
                dfs_reroot(next_node, root)
        
        dfs_reroot(0, -1)

        return res