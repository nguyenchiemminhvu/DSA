class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = [0] * n

        # left to right pass
        last_abs = 0
        for i in range(1, n):
            diff = nums[i] - nums[i - 1]
            last_abs = (last_abs + (diff * i))
            res[i] += last_abs

        # right to left pass
        last_abs = 0
        for i in range(n - 2, -1, -1):
            diff = nums[i + 1] - nums[i]
            last_abs = (last_abs + (diff * (n - 1 - i)))
            res[i] += last_abs

        return res