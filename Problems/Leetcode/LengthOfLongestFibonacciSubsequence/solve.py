from typing import List
from collections import defaultdict

class Solution:
    def lenLongestFibSubseq(self, arr: List[int]) -> int:
        n = len(arr)
        mp = defaultdict(int)
        for i, val in enumerate(arr):
            mp[val] = i

        res = 0
        for i2 in range(n - 2):
            for i1 in range(i2 + 1, n - 1):
                length = 2
                a, b = arr[i2], arr[i1]
                while True:
                    s = a + b
                    if s not in mp:
                        break
                    idx = mp[s]
                    length += 1
                    a, b = b, s
                
                if length >= 3:
                    res = max(res, length)
        return res