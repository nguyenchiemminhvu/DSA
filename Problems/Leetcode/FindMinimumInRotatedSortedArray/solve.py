from typing import List
import unittest

class Solution:
    def findMin(self, nums: List[int]) -> int:
        INF = 0x7FFFFFFF
        def find_min_binary_search(nums: List[int], left: int, right: int) -> int:
            if left > right:
                return INF
            if left == right:
                return nums[left]
            if nums[right] > nums[left]:
                return nums[left]
            
            mid = left + (right - left) // 2
            min_left = find_min_binary_search(nums, left, mid - 1)
            min_right = find_min_binary_search(nums, mid + 1, right)
            return min([nums[mid], min_left, min_right])
        
        return find_min_binary_search(nums, 0, len(nums) - 1)

class TestFindMinimumInRotatedSortedArray(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        nums = [3, 4, 5, 1, 2]
        expected = 1
        self.assertEqual(self.solution.findMin(nums), expected)

    def test_case_2(self):
        nums = [4, 5, 6, 7, 0, 1, 2]
        expected = 0
        self.assertEqual(self.solution.findMin(nums), expected)

    def test_case_3(self):
        nums = [11, 13, 15, 17]
        expected = 11
        self.assertEqual(self.solution.findMin(nums), expected)

    def test_case_4(self):
        nums = [2, 1]
        expected = 1
        self.assertEqual(self.solution.findMin(nums), expected)

    def test_case_5(self):
        nums = [1]
        expected = 1
        self.assertEqual(self.solution.findMin(nums), expected)

if __name__ == "__main__":
    unittest.main()