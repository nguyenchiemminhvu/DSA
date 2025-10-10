from typing import List
import unittest

class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        def lower_bound(nums: List[int], target: int) -> int:
            left = 0
            right = len(nums) - 1
            idx = len(nums)
            while left <= right:
                mid = left + (right - left) // 2
                if target <= nums[mid]:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx if idx < len(nums) else -1
        
        def upper_bound(nums: List[int], target: int) -> int:
            left = 0
            right = len(nums) - 1
            idx = len(nums)
            while left <= right:
                mid = left + (right - left) // 2
                if target < nums[mid]:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx
        
        lower = lower_bound(nums, target)
        if lower == -1 or nums[lower] != target:
            return [-1, -1]
        upper = upper_bound(nums, target)
        return [lower, upper - 1]

class TestFindFirstAndLastElementInSortedArray(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [5, 7, 7, 8, 8, 10]
        target = 8
        expected = [3, 4]
        self.assertEqual(self.solution.searchRange(nums, target), expected)

    def test_example2(self):
        nums = [5, 7, 7, 8, 8, 10]
        target = 6
        expected = [-1, -1]
        self.assertEqual(self.solution.searchRange(nums, target), expected)

    def test_example3(self):
        nums = []
        target = 0
        expected = [-1, -1]
        self.assertEqual(self.solution.searchRange(nums, target), expected)

    def test_single_element_found(self):
        nums = [1]
        target = 1
        expected = [0, 0]
        self.assertEqual(self.solution.searchRange(nums, target), expected)

    def test_single_element_not_found(self):
        nums = [1]
        target = 0
        expected = [-1, -1]
        self.assertEqual(self.solution.searchRange(nums, target), expected)

    def test_all_elements_same_as_target(self):
        nums = [2, 2, 2, 2]
        target = 2
        expected = [0, 3]
        self.assertEqual(self.solution.searchRange(nums, target), expected)

    def test_no_elements_same_as_target(self):
        nums = [1, 3, 5, 7]
        target = 4
        expected = [-1, -1]
        self.assertEqual(self.solution.searchRange(nums, target), expected)

if __name__ == "__main__":
    unittest.main()