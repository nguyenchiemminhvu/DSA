from typing import List

class Solution:
    def kthDistinct(self, arr: List[str], k: int) -> str:
        d = {}
        for val in arr:
            d[val] =  d.get(val, 0) + 1

        for val in arr:
            if d[val] == 1:
                k -= 1
            if k == 0:
                return val
        return ""