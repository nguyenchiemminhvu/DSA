from typing import List

class Solution:
    def canPlaceFlowers(self, bench: List[int], k: int) -> bool:
        for i, val in enumerate(bench):
            if bench[i] == 0:
                if i - 1 >= 0 and bench[i - 1] == 1:
                    continue
                if i + 1 < len(bench) and bench[i + 1] == 1:
                    continue
                bench[i] = 1
                k -= 1
        return k <= 0