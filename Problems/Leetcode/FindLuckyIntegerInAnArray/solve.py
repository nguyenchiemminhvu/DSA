from typing import List
from collections import Counter

class Solution:
    def findLucky(self, arr: List[int]) -> int:
        res = -1
        f = Counter(arr)
        for val in arr:
            if f[val] == val:
                res = max(res, val)
        return res