from typing import List
import unittest

class Solution:
    def shuffle(self, nums: List[int], n: int) -> List[int]:
        for i in range(n * 2):
            nums[i] = (nums[i] << 16)
        for i in range(n):
            nums[i * 2] |= (nums[i] >> 16)
        for i in range(n):
            nums[i * 2 + 1] |= (nums[i + n] >> 16)
        for i in range(n * 2):
            nums[i] = nums[i] & 0xFFFF
        return nums

class TestShuffleTheArray(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [2,5,1,3,4,7]
        n = 3
        expected = [2,3,5,4,1,7]
        self.assertEqual(self.solution.shuffle(nums, n), expected)

    def test_example2(self):
        nums = [1,2,3,4,4,3,2,1]
        n = 4
        expected = [1,4,2,3,3,2,4,1]
        self.assertEqual(self.solution.shuffle(nums, n), expected)

    def test_example3(self):
        nums = [1,1,2,2]
        n = 2
        expected = [1,2,1,2]
        self.assertEqual(self.solution.shuffle(nums, n), expected)

    def test_edge_case_min(self):
        nums = [0,0]
        n = 1
        expected = [0,0]
        self.assertEqual(self.solution.shuffle(nums, n), expected)

    def test_edge_case_max(self):
        nums = [10**3]*2000
        n = 1000
        expected = [10**3]*2000
        self.assertEqual(self.solution.shuffle(nums, n), expected)

if __name__ == "__main__":
    unittest.main()