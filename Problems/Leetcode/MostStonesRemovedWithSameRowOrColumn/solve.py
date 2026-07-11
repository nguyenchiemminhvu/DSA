from typing import List

class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)

        if root_i != root_j:
            if self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            elif self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1

class Solution:
    def removeStones(self, stones: List[List[int]]) -> int:
        n = len(stones)
        pos_to_id = {}
        for i, (x, y) in enumerate(stones):
            pos_to_id[(x, y)] = i
        
        dsu = DSU(n)
        for i in range(n):
            for j in range(i + 1, n):
                xi, yi = stones[i]
                xj, yj = stones[j]
                if xi == xj or yi == yj:
                    dsu.union(i, j)
        
        components = set()
        for i in range(n):
            components.add(dsu.find(i))
        return n - len(components)