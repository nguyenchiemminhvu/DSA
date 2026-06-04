from typing import List

class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        pivot = n

        for i in range(n - 2, -1, -1):
            if nums[i] < nums[i + 1]:
                pivot = i
                break
        
        if pivot == n:
            return nums.sort()
        
        swap_val = float('inf')
        swap_idx = pivot
        for i in range(n - 1, pivot, -1):
            if nums[i] > nums[pivot] and nums[i] < swap_val:
                swap_val = nums[i]
                swap_idx = i
        
        nums[pivot], nums[swap_idx] = nums[swap_idx], nums[pivot]
        nums[pivot + 1:] = sorted(nums[pivot + 1:])