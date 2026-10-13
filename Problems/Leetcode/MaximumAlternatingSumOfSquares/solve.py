class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:
        nums.sort(key=lambda x: x*x, reverse=True)
        n = len(nums)
        half = (n + 1) // 2

        res = 0
        for i in range(half):
            res += nums[i] ** 2
        for i in range(half, n):
            res -= nums[i] ** 2
        return res