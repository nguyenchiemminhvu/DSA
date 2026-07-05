class Solution:
    def isMiddleElementUnique(self, nums: list[int]) -> bool:
        n = len(nums)
        target = nums[n // 2]
        count = 0
        for val in nums:
            if val == target:
                count += 1
        return count == 1