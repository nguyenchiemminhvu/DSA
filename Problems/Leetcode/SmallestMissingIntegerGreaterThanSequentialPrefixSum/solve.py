from typing import List

class Solution:
    def missingInteger(self, nums: List[int]) -> int:
        s = set(nums)
        nums.append(100)
        n = len(nums)

        longest_sum = float('inf')
        for i in range(1, n):
            if nums[i] != nums[i - 1] + 1:
                longest_sum = min(longest_sum, sum(nums[0:i]))
                break

        while longest_sum in s:
            longest_sum += 1
        return longest_sum
