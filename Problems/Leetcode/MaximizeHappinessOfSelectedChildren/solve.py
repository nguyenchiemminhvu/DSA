from typing import List

class Solution:
    def maximumHappinessSum(self, nums: List[int], k: int) -> int:
        res = 0
        nums.sort(reverse=True)
        for i in range(k):
            if nums[i] > i:
                res += nums[i] - i
        return res