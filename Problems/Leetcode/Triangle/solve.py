from typing import List
import unittest

class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        if n == 1:
            return triangle[0][0]
        
        MAX = int(1e4 + 1)
        dp = [MAX] * n
        dp[0] = triangle[0][0]

        for i in range(1, n):
            cur_row = triangle[i]
            cur_row.extend([MAX] * (n - i))
            cur_row[0] += dp[0]
            for j in range(1, n):
                cur_row[j] = min(cur_row[j] + dp[j - 1], cur_row[j] + dp[j])
            dp = cur_row
        
        return min(dp)

class TestTriangle(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
        expected = 11
        self.assertEqual(self.solution.minimumTotal(triangle), expected)

    def test_case_2(self):
        triangle = [[-10]]
        expected = -10
        self.assertEqual(self.solution.minimumTotal(triangle), expected)

    def test_case_3(self):
        triangle = [[1],[2,3]]
        expected = 3
        self.assertEqual(self.solution.minimumTotal(triangle), expected)

    def test_case_4(self):
        triangle = [[-1],[2,3],[1,-1,-3]]
        expected = -1
        self.assertEqual(self.solution.minimumTotal(triangle), expected)

if __name__ == "__main__":
    unittest.main()