from typing import List

class Solution:
    def minCostToMoveChips(self, position: List[int]) -> int:
        prefix = [0] * 2
        for pos in position:
            prefix[pos & 1] += 1
        return min(prefix)