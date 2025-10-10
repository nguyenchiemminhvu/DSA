from typing import List
import unittest

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        def binary_search(nums: List[int], target: int, left: int, right: int) -> int:
            if left > right:
                return -1
            mid = left + (right - left) // 2
            if target == nums[mid]:
                return mid
            if nums[right] <= nums[left]:
                found_left = binary_search(nums, target, left, mid - 1)
                if found_left != -1:
                    return found_left
                else:
                    return binary_search(nums, target, mid + 1, right)
            else:
                if target == nums[mid]:
                    return mid
                if target > nums[mid]:
                    return binary_search(nums, target, mid + 1, right)
                else:
                    return binary_search(nums, target, left, mid - 1)
            return -1
        
        return binary_search(nums, target, 0, len(nums) - 1)

class TestSearchInRotatedSortedArray(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        nums = [4,5,6,7,0,1,2]
        target = 0
        expected = 4
        self.assertEqual(self.solution.search(nums, target), expected)

    def test_example2(self):
        nums = [4,5,6,7,0,1,2]
        target = 3
        expected = -1
        self.assertEqual(self.solution.search(nums, target), expected)

    def test_example3(self):
        nums = [1]
        target = 0
        expected = -1
        self.assertEqual(self.solution.search(nums, target), expected)

    def test_no_rotation(self):
        nums = [1,2,3,4,5]
        target = 3
        expected = 2
        self.assertEqual(self.solution.search(nums, target), expected)

    def test_single_element_found(self):
        nums = [1]
        target = 1
        expected = 0
        self.assertEqual(self.solution.search(nums, target), expected)

    def test_single_element_not_found(self):
        nums = [1]
        target = 2
        expected = -1
        self.assertEqual(self.solution.search(nums, target), expected)

    def test_large_array(self):
        nums = list(range(15, 100)) + list(range(0, 15))
        target = 10
        expected = 95
        self.assertEqual(self.solution.search(nums, target), expected)

if __name__ == "__main__":
    unittest.main()