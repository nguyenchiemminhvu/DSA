from typing import List
import unittest

class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m = len(matrix)
        n = len(matrix[0])
        total = m * n

        left = 0
        right = total - 1
        while left <= right:
            mid = left + (right - left) // 2
            # convert mid index to [row, col]
            r = mid // n
            c = mid % n
            if target == matrix[r][c]:
                return True
            if target < matrix[r][c]:
                right = mid - 1
            else:
                left = mid + 1

        return False

class TestSearchA2DMatrix(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        matrix = [
            [1, 3, 5, 7],
            [10, 11, 16, 20],
            [23, 30, 34, 60]
        ]
        target = 3
        self.assertTrue(self.solution.searchMatrix(matrix, target))

    def test_case_2(self):
        matrix = [
            [1, 3, 5, 7],
            [10, 11, 16, 20],
            [23, 30, 34, 60]
        ]
        target = 13
        self.assertFalse(self.solution.searchMatrix(matrix, target))

    def test_case_3(self):
        matrix = [[1]]
        target = 1
        self.assertTrue(self.solution.searchMatrix(matrix, target))

    def test_case_4(self):
        matrix = [[1]]
        target = 0
        self.assertFalse(self.solution.searchMatrix(matrix, target))

    def test_case_5(self):
        matrix = [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]
        ]
        target = 5
        self.assertTrue(self.solution.searchMatrix(matrix, target))

if __name__ == "__main__":
    unittest.main()