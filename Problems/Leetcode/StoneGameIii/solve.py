from typing import List

class Solution:
    def stoneGameIII(self, values: List[int]) -> str:
        n = len(values)
        
        from functools import lru_cache
        @lru_cache(None)
        def a_max_score(i: int) -> int:
            if i >= n:
                return 0
            
            take_1 = values[i] - a_max_score(i + 1)
            take_2 = float('-inf')
            if i + 1 < n:
                take_2 = values[i] + values[i + 1] - a_max_score(i + 2)
            take_3 = float('-inf')
            if i + 2 < n:
                take_3 = values[i] + values[i + 1] + values[i + 2] - a_max_score(i + 3)
            return max(take_1, take_2, take_3)
        
        a_score = a_max_score(0)
        if a_score == 0:
            return "Tie"
        if a_score > 0:
            return "Alice"
        return "Bob"