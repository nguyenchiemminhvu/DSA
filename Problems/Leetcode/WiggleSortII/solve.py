from typing import List

class Solution:
    def wiggleSort(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        nums.sort()
        n = len(nums)
        half = (n + 1) // 2
        small = nums[:half][::-1]
        large = nums[half:][::-1]
        nums[::2], nums[1::2] = small, large