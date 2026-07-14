from typing import List
import math

class Solution:
    def subsequencePairCount(self, nums: List[int]) -> int:
        n = len(nums)
        mod = 10**9 + 7

        from functools import lru_cache
        @lru_cache(None)
        def F(i: int, ga: int, gb: int) -> int:
            if i >= n:
                return ga > 0 and gb > 0 and ga == gb

            count = 0
            count += F(i + 1, ga, gb)
            count += F(i + 1, math.gcd(ga, nums[i]), gb)
            count += F(i + 1, ga, math.gcd(gb, nums[i]))
            count %= mod
            return count
        
        return F(0, 0, 0)