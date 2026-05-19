from typing import List

class Solution:
    def minCost(self, n: int, cost: List[List[int]]) -> int:
        from functools import lru_cache
        @lru_cache(None)
        def F(i: int, left_color: int, right_color: int) -> int:
            if i >= n // 2:
                return 0
            res = float('inf')
            for c1 in range(3):
                if c1 == left_color:
                    continue
                for c2 in range(3):
                    if c2 == c1 or c2 == right_color:
                        continue
                    res = min(
                        res,
                        cost[i][c1] + cost[n - i - 1][c2] + F(i + 1, c1, c2)
                    )
            return res
        return F(0, -1, -1)