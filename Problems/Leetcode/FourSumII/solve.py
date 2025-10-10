from typing import List
import unittest

class Solution:
    def fourSumCount(self, nums1: List[int], nums2: List[int], nums3: List[int], nums4: List[int]) -> int:
        res = 0
        count_sum_ab = {}
        for a in nums1:
            for b in nums2:
                s = a + b
                count_sum_ab[s] = count_sum_ab.get(s, 0) + 1
        
        for c in nums3:
            for d in nums4:
                target = -(c + d)
                res += count_sum_ab.get(target, 0)
        return res

class TestFourSumII(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums1 = [1,2]
        nums2 = [-2,-1]
        nums3 = [-1,2]
        nums4 = [0,2]
        expected = 2
        self.assertEqual(self.solution.fourSumCount(nums1, nums2, nums3, nums4), expected)

    def test_example2(self):
        nums1 = [0]
        nums2 = [0]
        nums3 = [0]
        nums4 = [0]
        expected = 1
        self.assertEqual(self.solution.fourSumCount(nums1, nums2, nums3, nums4), expected)

    def test_empty_arrays(self):
        nums1 = []
        nums2 = []
        nums3 = []
        nums4 = []
        expected = 0
        self.assertEqual(self.solution.fourSumCount(nums1, nums2, nums3, nums4), expected)

    def test_no_combinations(self):
        nums1 = [1]
        nums2 = [1]
        nums3 = [1]
        nums4 = [1]
        expected = 0
        self.assertEqual(self.solution.fourSumCount(nums1, nums2, nums3, nums4), expected)

if __name__ == "__main__":
    unittest.main()