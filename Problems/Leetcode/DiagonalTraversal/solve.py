from typing import List
import unittest

class Solution:
    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        lines = []

        m = len(mat)
        n = len(mat[0])
        extend_m = m + (n - 1)
        
        for i in range(0, extend_m):
            line = []
            r = i
            c = 0
            delta = r - (m - 1)
            if delta > 0:
                r = i - delta
                c += delta
            while r >= 0 and c < n:
                if (r >= 0 and r < m and c >= 0 and c < n):
                    line.append(mat[r][c])
                r -= 1
                c += 1
            lines.append(line)

        res = []
        should_reverse = False
        for line in lines:
            if should_reverse:
                line.reverse()
            res.extend(line)
            should_reverse = not should_reverse
        return res

class DiagonalTraversal(unittest.TestCase):
    def setUp(self):
        self.sol = Solution()

    def test_case_1(self):
        mat = [[1,2,3],[4,5,6],[7,8,9]]
        expected = [1,2,4,7,5,3,6,8,9]
        self.assertEqual(self.sol.findDiagonalOrder(mat), expected)

    def test_case_2(self):
        mat = [[1,2],[3,4]]
        expected = [1,2,3,4]
        self.assertEqual(self.sol.findDiagonalOrder(mat), expected)

    def test_case_3(self):
        mat = [[1]]
        expected = [1]
        self.assertEqual(self.sol.findDiagonalOrder(mat), expected)

    def test_case_4(self):
        mat = [[1,2,3,4,5]]
        expected = [1,2,3,4,5]
        self.assertEqual(self.sol.findDiagonalOrder(mat), expected)

    def test_case_5(self):
        mat = [[1],[2],[3],[4],[5]]
        expected = [1,2,3,4,5]
        self.assertEqual(self.sol.findDiagonalOrder(mat), expected)

if __name__ == "__main__":
    unittest.main()