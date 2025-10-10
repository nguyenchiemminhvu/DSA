from typing import List
import unittest

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        cur_min = 0xFFFFFFFF
        max_profit = 0
        for val in prices:
            max_profit = max(max_profit, val - cur_min)
            cur_min = min(cur_min, val)
        return max(0, max_profit)

class TestBestTimeToBuyAndSellStock(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        prices = [7,1,5,3,6,4]
        expected = 5
        self.assertEqual(self.solution.maxProfit(prices), expected)

    def test_example2(self):
        prices = [7,6,4,3,1]
        expected = 0
        self.assertEqual(self.solution.maxProfit(prices), expected)

    def test_single_day(self):
        prices = [5]
        expected = 0
        self.assertEqual(self.solution.maxProfit(prices), expected)

    def test_increasing_prices(self):
        prices = [1, 2, 3, 4, 5]
        expected = 4
        self.assertEqual(self.solution.maxProfit(prices), expected)

    def test_decreasing_prices(self):
        prices = [5, 4, 3, 2, 1]
        expected = 0
        self.assertEqual(self.solution.maxProfit(prices), expected)

    def test_fluctuating_prices(self):
        prices = [3, 2, 6, 5, 0, 3]
        expected = 4
        self.assertEqual(self.solution.maxProfit(prices), expected)

if __name__ == "__main__":
    unittest.main()