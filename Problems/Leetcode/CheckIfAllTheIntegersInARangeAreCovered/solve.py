from typing import List

class Solution:
    def isCovered(self, ranges: List[List[int]], left: int, right: int) -> bool:
        prefix = [0] * 100
        for l, r in ranges:
            prefix[l] += 1
            prefix[r + 1] -= 1

        for i in range(1, 100):
            prefix[i] += prefix[i - 1]
        
        for i in range(left, right + 1):
            if prefix[i] <= 0:
                return False
        return True