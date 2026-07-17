from typing import List

class DSU:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size
        self.components = size

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
            self.components -= 1
            return True
        return False

class Solution:
    def minTime(self, n: int, edges: List[List[int]], k: int) -> int:
        low, high = 0, 10**9
        res = high + 1
        while low <= high:
            mid = low + (high - low) // 2

            dsu = DSU(n)
            for u, v, t in edges:
                if t > mid:
                    dsu.union(u, v)
            
            valid = dsu.components >= k
            if valid:
                res = mid
                high = mid - 1
            else:
                low = mid + 1
        return res