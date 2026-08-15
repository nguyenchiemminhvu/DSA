class Solution:
    def minOperations(self, nums: list[int]) -> int:
        res = 0
        n = len(nums)
        i = 1
        for i in range(1, n):
            if nums[i] < nums[i - 1]:
                res += (nums[i-1] - nums[i])
        return res