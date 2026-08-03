from typing import List

class Solution:
    def stoneGameII(self, values: List[int]) -> int:
        n = len(values)

        suffix_sum = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            suffix_sum[i] = suffix_sum[i + 1] + values[i]
        
        from functools import lru_cache
        @lru_cache(None)
        def a_max_score(i: int, m: int) -> int:
            if i >= n:
                return 0
            
            if i + 2 * m >= n:
                return suffix_sum[i]
            
            max_score = 0
            for x in range(1, 2 * m + 1):
                next_player = a_max_score(i + x, max(m, x))
                cur_player = suffix_sum[i] - next_player
                max_score = max(max_score, cur_player)
            return max_score
        
        return a_max_score(0, 1)