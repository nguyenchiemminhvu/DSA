from typing import List
import unittest

class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        res = []
        left = 0
        right = len(matrix[0]) - 1
        up = 0
        down = len(matrix) - 1

        # directions : right -> down -> left -> up
        dir_r = [0, 1, 0, -1]
        dir_c = [1, 0, -1, 0]
        idir = 0

        r = 0
        c = 0
        visited: List[List[bool]] = [[False for _ in range(0, len(matrix[0]))] for _ in range(0, len(matrix))]
        visited[r][c] = True
        res.append(matrix[r][c])
        count = 1
        while count < len(matrix) * len(matrix[0]):
            next_r = r + dir_r[idir]
            next_c = c + dir_c[idir]
            if next_r >= up and next_r <= down and next_c >= left and next_c <= right:
                if not visited[next_r][next_c]:
                    count += 1
                    res.append(matrix[next_r][next_c])
                    visited[next_r][next_c] = True
                    r = next_r
                    c = next_c
                else:
                    idir = (idir + 1) % 4
            else:
                idir = (idir + 1) % 4

        return res

class TestSpiralMatrix(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        matrix = [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]
        ]
        expected_output = [1, 2, 3, 6, 9, 8, 7, 4, 5]
        self.assertEqual(self.solution.spiralOrder(matrix), expected_output)

    def test_case_2(self):
        matrix = [
            [1, 2, 3, 4],
            [5, 6, 7, 8],
            [9, 10, 11, 12]
        ]
        expected_output = [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]
        self.assertEqual(self.solution.spiralOrder(matrix), expected_output)

    def test_case_3(self):
        matrix = [[1]]
        expected_output = [1]
        self.assertEqual(self.solution.spiralOrder(matrix), expected_output)

    def test_case_4(self):
        matrix = [
            [1, 2],
            [3, 4]
        ]
        expected_output = [1, 2, 4, 3]
        self.assertEqual(self.solution.spiralOrder(matrix), expected_output)

if __name__ == "__main__":
    unittest.main()