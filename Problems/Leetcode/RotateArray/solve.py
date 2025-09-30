from typing import List
import unittest

class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        k %= len(nums)
        if k == 0:
            return
        
        pivot = len(nums) - k
        left = 0
        right = pivot - 1
        while left <= right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1
        
        left = pivot
        right = len(nums) - 1
        while left <= right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1
        
        left = 0
        right = len(nums) - 1
        while left <= right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1

class TestRotateArray(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_rotate(self):
        nums = [1,2,3,4,5,6,7]
        k = 3
        self.solution.rotate(nums, k)
        self.assertEqual(nums, [5,6,7,1,2,3,4])

        nums = [-1,-100,3,99]
        k = 2
        self.solution.rotate(nums, k)
        self.assertEqual(nums, [3,99,-1,-100])

        nums = [1]
        k = 0
        self.solution.rotate(nums, k)
        self.assertEqual(nums, [1])

        nums = [1]
        k = 1
        self.solution.rotate(nums, k)
        self.assertEqual(nums, [1])

        nums = [1,2]
        k = 3
        self.solution.rotate(nums, k)
        self.assertEqual(nums, [2,1])

if __name__ == "__main__":
    unittest.main()