from typing import List
from functools import lru_cache

class Solution:
    def canCross(self, stones: List[int]) -> bool:
        n = len(stones)
        mp = {}
        for i, pos in enumerate(stones):
            mp[pos] = i
        
        visited_state = set()
        @lru_cache(None)
        def F(i: int, last_jump_len: int) -> bool:
            if i < 0:
                return False
            if i >= n:
                return False
            if i == n - 1:
                return True
            
            if (i, last_jump_len) in visited_state:
                return False
            visited_state.add((i, last_jump_len))

            res = False
            for j in range(last_jump_len - 1, last_jump_len + 2):
                next_pos = stones[i] + j
                if next_pos not in mp:
                    continue
                next_idx = mp[next_pos]
                if F(next_idx, j):
                    res = True
                    break
            return res
        
        if stones[1] != stones[0] + 1:
            return False
        return F(1, 1)