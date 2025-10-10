from typing import List
import unittest

class Solution:
    def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:
        total_duration = 0

        start = timeSeries[0]
        end = start + duration
        for t in timeSeries:
            if t >= end:
                total_duration += end - start
                start = t
            end = t + duration
        return total_duration + (end - start)

class TestTeemoAttacking(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        timeSeries = [1, 4]
        duration = 2
        expected = 4
        self.assertEqual(self.solution.findPoisonedDuration(timeSeries, duration), expected)

    def test_example2(self):
        timeSeries = [1, 2]
        duration = 2
        expected = 3
        self.assertEqual(self.solution.findPoisonedDuration(timeSeries, duration), expected)

    def test_no_overlap(self):
        timeSeries = [1, 5, 10]
        duration = 2
        expected = 6
        self.assertEqual(self.solution.findPoisonedDuration(timeSeries, duration), expected)

    def test_full_overlap(self):
        timeSeries = [1, 2, 3]
        duration = 5
        expected = 7
        self.assertEqual(self.solution.findPoisonedDuration(timeSeries, duration), expected)

    def test_single_attack(self):
        timeSeries = [1]
        duration = 10
        expected = 10
        self.assertEqual(self.solution.findPoisonedDuration(timeSeries, duration), expected)

if __name__ == "__main__":
    unittest.main()