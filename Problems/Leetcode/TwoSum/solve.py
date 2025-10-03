from typing import List, Dict
import unittest

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        my_dict : Dict[int, List[int]] = {}
        for i, val in enumerate(nums):
            if (target - val) in my_dict:
                return [my_dict[target - val][0], i]

            if not val in my_dict:
                my_dict[val] = []
            my_dict[val].append(i)
        
        return []

class TestTwoSum(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        nums = [2,7,11,15]
        target = 9
        expected = [0,1]
        result = self.solution.twoSum(nums, target)
        self.assertEqual(result, expected)

    def test_case_2(self):
        nums = [3,2,4]
        target = 6
        expected = [1,2]
        result = self.solution.twoSum(nums, target)
        self.assertEqual(result, expected)

    def test_case_3(self):
        nums = [3,3]
        target = 6
        expected = [0,1]
        result = self.solution.twoSum(nums, target)
        self.assertEqual(result, expected)

    def test_case_4(self):
        nums = [1,2,3,4,5]
        target = 10
        expected = []
        result = self.solution.twoSum(nums, target)
        self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()