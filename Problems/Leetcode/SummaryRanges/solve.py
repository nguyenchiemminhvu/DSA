from typing import List
import unittest

class Solution:
    def summaryRanges(self, nums: List[int]) -> List[str]:
        res = []
        nums.append(0xFFFFFFFF)
        left = nums[0]
        right = left
        for i in range(1, len(nums)):
            if nums[i] == right + 1:
                right += 1
            else:
                if left == right:
                    res.append(str(left))
                else:
                    res.append(str(left) + '->' + str(right))
                left = nums[i]
                right = left
        return res

class TestSummaryRanges(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [0, 1, 2, 4, 5, 7]
        expected = ["0->2", "4->5", "7"]
        self.assertEqual(self.solution.summaryRanges(nums), expected)

    def test_example2(self):
        nums = [0, 2, 3, 4, 6, 8, 9]
        expected = ["0", "2->4", "6", "8->9"]
        self.assertEqual(self.solution.summaryRanges(nums), expected)

    def test_empty(self):
        nums = []
        expected = []
        self.assertEqual(self.solution.summaryRanges(nums), expected)

    def test_single_element(self):
        nums = [-1]
        expected = ["-1"]
        self.assertEqual(self.solution.summaryRanges(nums), expected)

    def test_no_consecutive(self):
        nums = [1, 3, 5, 7]
        expected = ["1", "3", "5", "7"]
        self.assertEqual(self.solution.summaryRanges(nums), expected)

    def test_all_consecutive(self):
        nums = [1, 2, 3, 4, 5]
        expected = ["1->5"]
        self.assertEqual(self.solution.summaryRanges(nums), expected)

if __name__ == "__main__":
    unittest.main()