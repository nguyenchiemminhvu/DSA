from typing import List
import unittest

class Solution:
    def dailyTemperatures(self, temp: List[int]) -> List[int]:
        n = len(temp)
        res = [0] * n

        st = [(temp[-1], n - 1)] # (val, idx)
        for i in range(n - 2, -1, -1):
            while len(st) > 0 and temp[i] >= st[-1][0]:
                st.pop()
            
            if len(st) > 0:
                res[i] = (st[-1][1] - i)
            
            st.append((temp[i], i))
        
        return res

class TestDailyTemperatures(unittest.TestCase):
    def setUp(self):
        self.sol = Solution()

    def test_example1(self):
        temp = [73, 74, 75, 71, 69, 72, 76, 73]
        expected = [1, 1, 4, 2, 1, 1, 0, 0]
        self.assertEqual(self.sol.dailyTemperatures(temp), expected)

    def test_example2(self):
        temp = [30, 40, 50, 60]
        expected = [1, 1, 1, 0]
        self.assertEqual(self.sol.dailyTemperatures(temp), expected)

    def test_example3(self):
        temp = [30, 60, 90]
        expected = [1, 1, 0]
        self.assertEqual(self.sol.dailyTemperatures(temp), expected)

    def test_no_warmer_days(self):
        temp = [90, 80, 70]
        expected = [0, 0, 0]
        self.assertEqual(self.sol.dailyTemperatures(temp), expected)

    def test_all_same_temperatures(self):
        temp = [70, 70, 70]
        expected = [0, 0, 0]
        self.assertEqual(self.sol.dailyTemperatures(temp), expected)

    def test_single_day(self):
        temp = [100]
        expected = [0]
        self.assertEqual(self.sol.dailyTemperatures(temp), expected)

if __name__ == "__main__":
    unittest.main()
