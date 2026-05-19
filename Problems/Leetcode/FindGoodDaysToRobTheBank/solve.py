from typing import List

class Solution:
    def goodDaysToRobBank(self, nums: List[int], time: int) -> List[int]:
        n = len(nums)

        left = [1] * n
        right = [1] * n

        for i in range(1, n):
            if nums[i] <= nums[i - 1]:
                left[i] = left[i - 1] + 1
        
        for i in range(n - 2, -1, -1):
            if nums[i] <= nums[i + 1]:
                right[i] = right[i + 1] + 1
        
        res = []
        for i in range(time, n - time):
            if left[i] > time and right[i] > time:
                res.append(i)
        return res