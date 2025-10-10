from typing import List
import unittest

class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        min_len = 0xFFFFFFFF
        
        n = len(nums)
        left = 0
        right = 0
        cur_sum = 0
        while right < n:
            cur_sum += nums[right]
            while cur_sum >= target:
                min_len = min(min_len, right - left + 1)
                cur_sum -= nums[left]
                left += 1
            right += 1
        
        return 0 if min_len == 0xFFFFFFFF else min_len

class TestMinimumSizeSubarraySum(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        target = 7
        nums = [2,3,1,2,4,3]
        expected = 2
        self.assertEqual(self.solution.minSubArrayLen(target, nums), expected)

    def test_case_2(self):
        target = 4
        nums = [1,4,4]
        expected = 1
        self.assertEqual(self.solution.minSubArrayLen(target, nums), expected)

    def test_case_3(self):
        target = 11
        nums = [1,1,1,1,1,1,1,1]
        expected = 0
        self.assertEqual(self.solution.minSubArrayLen(target, nums), expected)

    def test_case_4(self):
        target = 15
        nums = [5,1,3,5,10,7,4,9,2,8]
        expected = 2
        self.assertEqual(self.solution.minSubArrayLen(target, nums), expected)

    def test_case_5(self):
        target = 100
        nums = [1,2,3,4,5]
        expected = 0
        self.assertEqual(self.solution.minSubArrayLen(target, nums), expected)

if __name__ == "__main__":
    unittest.main()