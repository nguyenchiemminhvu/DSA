from typing import List
import unittest

class Solution:
    def __init__(self):
        self.memo = {}

    def numSquares(self, n: int) -> int:
        def F(n: int) -> int: # F(i) -> minimum number of coins sum to i
            if n == 0:
                return 0
            if n in self.memo:
                return self.memo[n]
            
            min_coins = float('inf')
            j = 1
            while j * j <= n:
                min_coins = min(min_coins, 1 + F(n - j * j))
                j += 1
            self.memo[n] = min_coins
            return min_coins
        
        return F(n)

class TestPerfectSquares(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        self.assertEqual(self.solution.numSquares(12), 3)

    def test_case_2(self):
        self.assertEqual(self.solution.numSquares(13), 2)

    def test_case_3(self):
        self.assertEqual(self.solution.numSquares(1), 1)

    def test_case_4(self):
        self.assertEqual(self.solution.numSquares(0), 0)

    def test_case_5(self):
        self.assertEqual(self.solution.numSquares(100), 1)

if __name__ == "__main__":
    unittest.main()
