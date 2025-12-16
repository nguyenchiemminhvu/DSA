from collections import defaultdict
from typing import List

class Solution:
    def beautifulSubsets(self, nums: List[int], k: int) -> int:
        nums.sort()
        used = defaultdict(int)
        res = 0

        def dfs(i):
            nonlocal res
            if i == len(nums):
                return

            # Option 1: skip nums[i]
            dfs(i + 1)

            # Option 2: take nums[i] if valid
            val = nums[i]
            if used[val - k] == 0 and used[val + k] == 0:
                used[val] += 1
                res += 1        # count this new subset
                dfs(i + 1)
                used[val] -= 1

        dfs(0)
        return res
