from typing import List
import unittest

class Solution:
    def triangleNumber(self, nums: List[int]) -> int:
        nums.sort()
        count = 0
        for c in range(len(nums) - 1, 1, -1):
            a, b = 0, c - 1
            while (a < b):
                if nums[a] + nums[b] <= nums[c]:
                    a += 1
                else:
                    count += (b - a)
                    b -= 1
        return count

class TestValidTriangleNumber(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [2, 2, 3, 4]
        expected = 3
        self.assertEqual(self.solution.triangleNumber(nums), expected)

    def test_example2(self):
        nums = [4, 2, 3, 4]
        expected = 4
        self.assertEqual(self.solution.triangleNumber(nums), expected)

if __name__ == "__main__":
    unittest.main()