from typing import List

class Solution:
    def findOrder(self, n: int, pre: List[List[int]]) -> List[int]:
        graph = [
            [] for i in range(n)
        ]

        for c, p in pre:
            graph[p].append(c)
        
        visited = set()
        recur_st = set()
        def dfs(cur:int, topo: List[int]):
            visited.add(cur)
            recur_st.add(cur)
            for adj in graph[cur]:
                if adj not in visited:
                    if not dfs(adj, topo):
                        return False
                if adj in recur_st:
                    return False
            recur_st.remove(cur)
            topo.append(cur)
            return True

        def build_topo() -> List[int]:
            topo = []
            for i in range(n):
                if i not in visited:
                    if not dfs(i, topo):
                        return []
            topo.reverse()
            return topo
        
        return build_topo()