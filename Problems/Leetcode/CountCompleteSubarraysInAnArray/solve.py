from collections import Counter
from typing import List

class Solution:
    def countCompleteSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        fn = Counter(nums)

        res = 0
        l = 0
        fa = Counter()
        for r in range(n):
            fa[nums[r]] += 1

            while len(fa) == len(fn):
                res += n - r

                fa[nums[l]] -= 1
                if fa[nums[l]] <= 0:
                    fa.pop(nums[l])
                l += 1
        
        return res