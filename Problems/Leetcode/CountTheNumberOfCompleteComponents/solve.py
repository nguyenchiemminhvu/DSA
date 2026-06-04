from collections import defaultdict
from typing import List

class DSU:
    def __init__(self, n):
        self.parent = [i for i in range(n)]
        self.rank = [1] * n
    
    def find(self, x):
        # Path compression: compress the tree height dynamically
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        # Find the representatives (roots)  of the sets
        root_x = self.find(x)
        root_y = self.find(y)
        
        # If they are already in the same set, do nothing
        if root_x == root_y:
            return False
            
        # Union by rank: attach the shorter tree under the taller tree
        if self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        elif self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1
            
        return True

class Solution:
    def countCompleteComponents(self, n: int, edges: List[List[int]]) -> int:
        counter = defaultdict(int)
        dsu = DSU(n)
        for x, y in edges:
            dsu.union(x, y)
            counter[x] += 1
            counter[y] += 1
        
        groups = defaultdict(list)
        for i in range(n):
            groups[dsu.find(i)].append(i)
        
        res = 0
        for root, arr in groups.items():
            valid = True
            for i in arr:
                if counter[i] != len(arr) - 1:
                    valid = False
                    break
            res += valid
            
        return res