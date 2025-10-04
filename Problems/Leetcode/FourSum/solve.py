from typing import List
import unittest

class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        res = set()
        nums.sort()
        n = len(nums)
        for i in range(0, n):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            for j in range(i + 1, n):
                if j > i + 1 and nums[j] == nums[j - 1]:
                    continue
                remain = target - (nums[i] + nums[j])
                left = j + 1
                right = n - 1
                while left < right:
                    if remain == nums[left] + nums[right]:
                        res.add((nums[i], nums[j], nums[left], nums[right]))
                        while left < right and nums[left] == nums[left + 1]:
                            left += 1
                        while left < right and nums[right] == nums[right - 1]:
                            right -= 1
                        left += 1
                        right -= 1
                    elif remain > nums[left] + nums[right]:
                        left += 1
                    else:
                        right -= 1
        return [list(t) for t in res]

class TestFourSum(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        nums = [1, 0, -1, 0, -2, 2]
        target = 0
        expected = sorted([[-1, 0, 0, 1], [-2, -1, 1, 2], [-2, 0, 0, 2]])
        result = sorted(self.solution.fourSum(nums, target))
        self.assertEqual(result, expected)

    def test_case_2(self):
        nums = [2, 2, 2, 2, 2]
        target = 8
        expected = [[2, 2, 2, 2]]
        result = self.solution.fourSum(nums, target)
        self.assertEqual(result, expected)

    def test_case_3(self):
        nums = [0, 0, 0, 0]
        target = 0
        expected = [[0, 0, 0, 0]]
        result = self.solution.fourSum(nums, target)
        self.assertEqual(result, expected)

    def test_case_4(self):
        nums = [-3,-2,-1,0,0,1,2,3]
        target = 0
        expected = sorted([[-3,-2,2,3],[-3,-1,1,3],[-3,0,0,3],[-3,0,1,2],[-2,-1,0,3],[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]])
        result = sorted(self.solution.fourSum(nums, target))
        self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()