from typing import List

class Solution:
    def canBeEqual(self, target: List[int], arr: List[int]) -> bool:
        f = {}
        for val in arr:
            f[val] = f.get(val, 0) + 1
        for val in target:
            if val not in f:
                return False
            f[val] -= 1
            if f[val] < 0:
                return False
        return True