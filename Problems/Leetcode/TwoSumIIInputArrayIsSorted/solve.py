from typing import List
import unittest

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        left = 0
        right = len(nums) - 1
        while left <= right:
            s = nums[left] + nums[right]
            if s == target:
                return [left + 1, right + 1]
            if s < target:
                left += 1
            else:
                right -= 1
        return [-1]

class TestTwoSumII(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [2, 7, 11, 15]
        target = 9
        expected = [1, 2]
        self.assertEqual(self.solution.twoSum(nums, target), expected)

    def test_example2(self):
        nums = [2, 3, 4]
        target = 6
        expected = [1, 3]
        self.assertEqual(self.solution.twoSum(nums, target), expected)

    def test_example3(self):
        nums = [-1, 0]
        target = -1
        expected = [1, 2]
        self.assertEqual(self.solution.twoSum(nums, target), expected)

    def test_no_solution(self):
        nums = [1, 2, 3]
        target = 7
        expected = [-1]
        self.assertEqual(self.solution.twoSum(nums, target), expected)

if __name__ == "__main__":
    unittest.main()