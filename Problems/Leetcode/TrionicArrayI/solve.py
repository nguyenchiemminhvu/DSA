from typing import List

class Solution:
    def isTrionic(self, nums: List[int]) -> bool:
        n = len(nums)
        prefix = [1] * n
        for i in range(1, n):
            if nums[i] == nums[i - 1]:
                return False
            if nums[i] - nums[i - 1] < 0:
                prefix[i] = -1
        left = 0
        right = n - 1
        while left < right and prefix[left] == 1:
            left += 1
        while left < right and prefix[right] == 1:
            right -= 1
        return prefix[0] == 1 and prefix[1] == 1 and prefix[-1] == 1 and left <= right and all(val == -1 for val in prefix[left:right + 1])