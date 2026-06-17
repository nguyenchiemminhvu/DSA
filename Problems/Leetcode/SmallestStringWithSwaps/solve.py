from collections import defaultdict
from typing import List

class DSU:
    def __init__(self, n: int):
        self.n = n
        self.parent = [i for i in range(n)]
        self.rank = [1] * n
    
    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        
        if self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        elif self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1

        return True
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

class Solution:
    def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
        n = len(s)
        s = list(s)

        dsu = DSU(n)
        for a, b in pairs:
            dsu.union(a, b)
        
        mp = defaultdict(list)
        for i in range(n):
            root = dsu.find(i)
            mp[root].append((s[i], i))
        
        for root, arr in mp.items():
            arr.sort()
            indices = sorted([i for _, i in arr])
            n = len(arr)
            for i in range(n):
                s[indices[i]] = arr[i][0]
        
        return ''.join(s)