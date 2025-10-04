from typing import List
import unittest

class Solution:
    def maxArea(self, height: List[int]) -> int:
        res = 0
        
        n = len(height)
        left = 0
        right = n - 1
        while left < right:
            res = max(res, min(height[left], height[right]) * (right - left))
            if height[left] <= height[right]:
                left += 1
            elif height[left] > height[right]:
                right -= 1
        return res

class TestContainerWithMostWater(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        height = [1,8,6,2,5,4,8,3,7]
        expected = 49
        self.assertEqual(self.solution.maxArea(height), expected)

    def test_example2(self):
        height = [1,1]
        expected = 1
        self.assertEqual(self.solution.maxArea(height), expected)

    def test_additional_case1(self):
        height = [4,3,2,1,4]
        expected = 16
        self.assertEqual(self.solution.maxArea(height), expected)

    def test_additional_case2(self):
        height = [1,2,1]
        expected = 2
        self.assertEqual(self.solution.maxArea(height), expected)

if __name__ == "__main__":
    unittest.main()