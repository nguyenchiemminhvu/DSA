from typing import List

class Solution:
    def predictTheWinner(self, nums: List[int]) -> bool:
        from functools import lru_cache
        @lru_cache(None)
        def p1_try_max_score(l: int, r: int) -> int:
            if l > r:
                return 0
            if l == r:
                return nums[l]
            
            pick_left = nums[l] + min(
                p1_try_max_score(l + 2, r),
                p1_try_max_score(l + 1, r - 1)
            )

            pick_right = nums[r] + min(
                p1_try_max_score(l, r - 2),
                p1_try_max_score(l + 1, r - 1)
            )

            return max(pick_left, pick_right)
        
        p1_score = p1_try_max_score(0, len(nums) - 1)
        p2_score = sum(nums) - p1_score
        return p1_score >= p2_score