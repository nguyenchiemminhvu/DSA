from typing import List

class DSU:
    def __init__(self, size: int):
        self.parent = list(range(size))

    def find(self, i: int) -> int:
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, i: int, j: int) -> bool:
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i == root_j:
            return False  # Cycle detected
        self.parent[root_i] = root_j
        return True

class Solution:
    def findRedundantDirectedConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        parents = [0] * (n + 1)
        edge1 = None
        edge2 = None

        for u, v in edges:
            if parents[v] != 0:
                edge1 = [parents[v], v]
                edge2 = [u, v]
                break
            parents[v] = u
        
        dsu = DSU(n + 1)
        for u, v in edges:
            if [u, v] == edge2:
                continue
            
            if not dsu.union(u, v):
                if edge1:
                    return edge1
                return [u, v]
        
        return edge2