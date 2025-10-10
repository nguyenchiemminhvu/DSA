from typing import List
import unittest

class Solution:
    def numIdenticalPairs(self, nums: List[int]) -> int:
        d = {}
        for val in nums:
            d[val] = d.get(val, 0) + 1
        count_pair = 0
        for k, v in d.items():
            count_pair += (v * (v - 1) // 2)
        return count_pair

class TestNumberOfGoodPairs(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [1, 2, 3, 1, 1, 3]
        expected_output = 4
        self.assertEqual(self.solution.numIdenticalPairs(nums), expected_output)

    def test_example2(self):
        nums = [1, 1, 1, 1]
        expected_output = 6
        self.assertEqual(self.solution.numIdenticalPairs(nums), expected_output)

    def test_example3(self):
        nums = [1, 2, 3]
        expected_output = 0
        self.assertEqual(self.solution.numIdenticalPairs(nums), expected_output)

    def test_empty_array(self):
        nums = []
        expected_output = 0
        self.assertEqual(self.solution.numIdenticalPairs(nums), expected_output)

    def test_single_element(self):
        nums = [5]
        expected_output = 0
        self.assertEqual(self.solution.numIdenticalPairs(nums), expected_output)

    def test_all_unique_elements(self):
        nums = [1, 2, 3, 4, 5]
        expected_output = 0
        self.assertEqual(self.solution.numIdenticalPairs(nums), expected_output)

    def test_large_input(self):
        nums = [i % 100 for i in range(1000)]
        expected_output = sum((v * (v - 1) // 2) for v in [10] * 100)
        self.assertEqual(self.solution.numIdenticalPairs(nums), expected_output)

if __name__ == "__main__":
    unittest.main()