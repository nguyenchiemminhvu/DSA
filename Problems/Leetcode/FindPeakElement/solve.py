from typing import List
import unittest

class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        def find_peak_binary_search(nums: List[int], left: int, right: int) -> int:
            if left > right:
                return -1
            mid = left + (right - left) // 2
            if nums[mid] > nums[mid - 1] and nums[mid] > nums[mid + 1]:
                return mid
            peak_left = find_peak_binary_search(nums, left, mid - 1)
            if peak_left != -1:
                return peak_left
            return find_peak_binary_search(nums, mid + 1, right)
        
        if len(nums) == 1:
            return 0
        if nums[0] > nums[1]:
            return 0
        if nums[-1] > nums[-2]:
            return len(nums) - 1
        
        return find_peak_binary_search(nums, 1, len(nums) - 2)

class TestFindPeakElement(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [1, 2, 3, 1]
        result = self.solution.findPeakElement(nums)
        self.assertIn(result, [2])

    def test_example2(self):
        nums = [1, 2, 1, 3, 5, 6, 4]
        result = self.solution.findPeakElement(nums)
        self.assertIn(result, [1, 5])

    def test_single_element(self):
        nums = [1]
        result = self.solution.findPeakElement(nums)
        self.assertEqual(result, 0)

    def test_two_elements(self):
        nums = [2, 1]
        result = self.solution.findPeakElement(nums)
        self.assertEqual(result, 0)

    def test_increasing_sequence(self):
        nums = [1, 2, 3, 4, 5]
        result = self.solution.findPeakElement(nums)
        self.assertEqual(result, 4)

    def test_decreasing_sequence(self):
        nums = [5, 4, 3, 2, 1]
        result = self.solution.findPeakElement(nums)
        self.assertEqual(result, 0)

if __name__ == "__main__":
    unittest.main()