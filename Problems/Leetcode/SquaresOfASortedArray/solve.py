from typing import List
import math
import unittest

class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        n = len(nums)

        left = 0
        right = n - 1
        res = []
        while (left <= right):
            if abs(nums[left]) >= abs(nums[right]):
                res.append(nums[left] ** 2)
                left += 1
            else:
                res.append(nums[right] ** 2)
                right -= 1

        res.reverse()
        return res

class TestSquaresOfASortedArray(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [-4, -1, 0, 3, 10]
        expected = [0, 1, 9, 16, 100]
        self.assertEqual(self.solution.sortedSquares(nums), expected)

    def test_example2(self):
        nums = [-7, -3, 2, 3, 11]
        expected = [4, 9, 9, 49, 121]
        self.assertEqual(self.solution.sortedSquares(nums), expected)

    def test_all_negative(self):
        nums = [-5, -4, -3, -2, -1]
        expected = [1, 4, 9, 16, 25]
        self.assertEqual(self.solution.sortedSquares(nums), expected)

    def test_all_positive(self):
        nums = [1, 2, 3, 4, 5]
        expected = [1, 4, 9, 16, 25]
        self.assertEqual(self.solution.sortedSquares(nums), expected)

    def test_mixed_values(self):
        nums = [-3, -1, 0, 1, 2]
        expected = [0, 1, 1, 4, 9]
        self.assertEqual(self.solution.sortedSquares(nums), expected)

    def test_single_element(self):
        nums = [-2]
        expected = [4]
        self.assertEqual(self.solution.sortedSquares(nums), expected)

    def test_empty_array(self):
        nums = []
        expected = []
        self.assertEqual(self.solution.sortedSquares(nums), expected)

if __name__ == "__main__":
    unittest.main()