from collections import defaultdict
from typing import List

class DSU:
    def __init__(self, size: int):
        self.parent = list(range(size))
        self.size = [1] * size

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x == root_y:
            return False

        if self.size[root_x] < self.size[root_y]:
            root_x, root_y = root_y, root_x

        self.parent[root_y] = root_x
        self.size[root_x] += self.size[root_y]
        return True

class Solution:
    def largestComponentSize(self, nums: List[int]) -> int:
        n = len(nums)
        dsu = DSU(n)

        mp = {}
        for i, val in enumerate(nums):
            d = 2
            temp = val
            while d * d <= val:
                if temp % d == 0:
                    if d not in mp:
                        mp[d] = i
                    else:
                        dsu.union(i, mp[d])
                    
                    while temp % d == 0 and temp > 1:
                        temp //= d
                
                d += 1
            
            if temp > 1:
                # prime number:
                if temp not in mp:
                    mp[temp] = i
                else:
                    dsu.union(i, mp[temp])
        
        mp = defaultdict(int)
        for i in range(n):
            root = dsu.find(i)
            mp[root] += 1
        return max(mp.values())