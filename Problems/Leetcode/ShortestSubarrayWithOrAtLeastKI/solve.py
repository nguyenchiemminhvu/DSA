from typing import List

class Solution:
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        n = len(nums)

        def F(i:int) -> int:
            if i >= n:
                return float('inf')
            res = float('inf')
            val = 0
            for j in range(i, n):
                val |= nums[j]
                if val >= k:
                    res = min(res, j - i + 1)
                    break
            res = min(res, F(i + 1))
            return res
          
        res = F(0)
        return -1 if res == float('inf') else res