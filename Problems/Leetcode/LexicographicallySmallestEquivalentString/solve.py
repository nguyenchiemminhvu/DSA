from collections import defaultdict
import heapq

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
            if self.rank[root_i] > self.rank[root_j]:
                self.parent[root_j] = root_i
            elif self.rank[root_i] < self.rank[root_j]:
                self.parent[root_i] = root_j
            else:
                self.parent[root_j] = root_i
                self.rank[root_i] += 1

class Solution:
    def smallestEquivalentString(self, s1: str, s2: str, base: str) -> str:
        dsu = DSU(26)

        for i in range(len(s1)):
            i1, i2 = ord(s1[i]) - ord('a'), ord(s2[i]) - ord('a')
            dsu.union(i1, i2)
        
        groups = {}
        for i in range(26):
            root = dsu.find(i)
            if root not in groups:
                groups[root] = []
            heapq.heappush(groups[root], i)
        
        res = []
        for c in base:
            i = ord(c) - ord('a')
            root = dsu.find(i)
            min_lex = groups[root][0]
            res.append(chr(ord('a') + min_lex))

        return "".join(res)