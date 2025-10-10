from typing import List
import unittest

class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        s = set()
        for val in nums:
            if val in s:
                return val
            s.add(val)
        return -1

class TestFindTheDuplicateNumber(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [1, 3, 4, 2, 2]
        expected = 2
        self.assertEqual(self.solution.findDuplicate(nums), expected)

    def test_example2(self):
        nums = [3, 1, 3, 4, 2]
        expected = 3
        self.assertEqual(self.solution.findDuplicate(nums), expected)

    def test_no_duplicate(self):
        nums = [1, 2, 3, 4, 5]
        expected = -1
        self.assertEqual(self.solution.findDuplicate(nums), expected)

    def test_multiple_duplicates(self):
        nums = [1, 2, 3, 4, 2, 3]
        expected = 2
        self.assertEqual(self.solution.findDuplicate(nums), expected)

if __name__ == "__main__":
    unittest.main()