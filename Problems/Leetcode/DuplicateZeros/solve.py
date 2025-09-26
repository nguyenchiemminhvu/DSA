from typing import List
import unittest

class Solution:
    def duplicateZeros(self, arr: List[int]) -> None:
        """
        Do not return anything, modify arr in-place instead.
        """
        n = len(arr)
        count_zero = arr.count(0)
        arr.extend([0] * count_zero)
        i = n - 1
        i_new = i + count_zero
        while i >= 0:
            if arr[i] == 0:
                arr[i_new], arr[i_new - 1] = 0, 0
                i_new -= 2
            else:
                arr[i_new] = arr[i]
                i_new -= 1
            i -= 1

        while (count_zero):
            arr.pop()
            count_zero -= 1

class TestDuplicateZeros(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        arr = [1,0,2,3,0,4,5,0]
        self.solution.duplicateZeros(arr)
        self.assertEqual(arr, [1,0,0,2,3,0,0,4])

    def test_example2(self):
        arr = [1,2,3]
        self.solution.duplicateZeros(arr)
        self.assertEqual(arr, [1,2,3])

    def test_no_zeros(self):
        arr = [4,5,6]
        self.solution.duplicateZeros(arr)
        self.assertEqual(arr, [4,5,6])

    def test_all_zeros(self):
        arr = [0,0,0]
        self.solution.duplicateZeros(arr)
        self.assertEqual(arr, [0,0,0])

    def test_single_zero(self):
        arr = [1,0]
        self.solution.duplicateZeros(arr)
        self.assertEqual(arr, [1,0])

    def test_empty_array(self):
        arr = []
        self.solution.duplicateZeros(arr)
        self.assertEqual(arr, [])

if __name__ == "__main__":
    unittest.main()