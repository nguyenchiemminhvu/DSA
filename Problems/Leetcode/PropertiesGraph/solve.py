from typing import List

class DSU:
    def __init__(self, n: int):
        self.n = n
        self.parents = [i for i in range(n)]
        self.ranks = [1] * n
        self.components = n
    
    def union(self, x: int, y: int) -> bool:
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            if self.ranks[root_x] < self.ranks[root_y]:
                root_x, root_y = root_y, root_x
            self.parents[root_y] = root_x
            self.ranks[root_x] += self.ranks[root_y]
            self.components -= 1
            return True
        return False
    
    def find(self, x: int) -> int:
        if self.parents[x] != x:
            self.parents[x] = self.find(self.parents[x])
        return self.parents[x]

class Solution:
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        m = len(properties[0])

        dsu = DSU(n)

        s = [set()] * n
        for i in range(n):
            s[i] = set(properties[i])
        
        for i in range(n):
            for j in range(i + 1, n):
                if i == j:
                    continue
                if len(s[i] & s[j]) >= k:
                    dsu.union(i, j)
        return dsu.components