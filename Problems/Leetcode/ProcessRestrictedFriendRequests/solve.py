from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

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
    
    def connected(self, i, j):
        return self.find(i) == self.find(j)

class Solution:
    def friendRequests(self, n: int, restrictions: List[List[int]], requests: List[List[int]]) -> List[bool]:
        nr = len(requests)
        res = [False] * nr

        dsu_request = DSU(n)
        
        for i, (u, v) in enumerate(requests):
            ru, rv = dsu_request.find(u), dsu_request.find(v)
            valid = True
            for x, y in restrictions:
                rx, ry = dsu_request.find(x), dsu_request.find(y)
                if (ru == rx and rv == ry) or (ru == ry and rv == rx):
                    valid = False
                    break

            res[i] = valid
            if valid:
                dsu_request.union(u, v)

        return res