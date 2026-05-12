from typing import List

class Solution:
    def canFinish(self, n: int, pre: List[List[int]]) -> bool:
        graph = [
            [] for i in range(n)
        ]

        for c, p in pre:
            graph[p].append(c)

        visited = set()
        recur_st = set()
        def has_cycle(cur: int):
            visited.add(cur)
            recur_st.add(cur)
            for adj in graph[cur]:
                if adj not in visited:
                    if has_cycle(adj):
                        return True
                else:
                    if adj in recur_st:
                        return True
            recur_st.remove(cur)
            return False
        
        for i in range(n):
            if i not in visited:
                if has_cycle(i):
                    return False
        return True