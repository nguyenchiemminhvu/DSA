from typing import List
import unittest

class Solution:
    def sortArray(self, nums: List[int]) -> List[int]:
        def merge_two_sorted_segment(arr: List[int], left: int, mid: int, right: int):
            temp = []
            ileft = left
            iright = mid + 1
            while ileft <= mid and iright <= right:
                if arr[ileft] <= arr[iright]:
                    temp.append(arr[ileft])
                    ileft += 1
                else:
                    temp.append(arr[iright])
                    iright += 1
            while ileft <= mid:
                temp.append(arr[ileft])
                ileft += 1
            while iright <= right:
                temp.append(arr[iright])
                iright += 1
            for i in range(left, right + 1):
                arr[i] = temp[i - left]
        
        def merge_sort(arr: List[int], left: int, right: int):
            if left < right:
                mid = left + (right - left) // 2
                merge_sort(arr, left, mid)
                merge_sort(arr, mid + 1, right)
                merge_two_sorted_segment(arr, left, mid, right)
        
        merge_sort(nums, 0, len(nums) - 1)
        return nums

class TestSortAnArray(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        nums = [5, 2, 3, 1]
        expected = [1, 2, 3, 5]
        self.assertEqual(self.solution.sortArray(nums), expected)

    def test_case_2(self):
        nums = [5, 1, 1, 2, 0, 0]
        expected = [0, 0, 1, 1, 2, 5]
        self.assertEqual(self.solution.sortArray(nums), expected)

    def test_case_3(self):
        nums = []
        expected = []
        self.assertEqual(self.solution.sortArray(nums), expected)

    def test_case_4(self):
        nums = [3]
        expected = [3]
        self.assertEqual(self.solution.sortArray(nums), expected)

    def test_case_5(self):
        nums = [2, 1]
        expected = [1, 2]
        self.assertEqual(self.solution.sortArray(nums), expected)

if __name__ == "__main__":
    unittest.main()