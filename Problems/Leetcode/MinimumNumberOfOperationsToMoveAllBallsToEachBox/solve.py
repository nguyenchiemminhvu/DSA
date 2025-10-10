from typing import List
import unittest

class Solution:
    def minOperations(self, boxes: str) -> List[int]:
        n = len(boxes)

        left = [0] * n
        right = [0] * n

        count = 0
        for i in range(0, n):
            if i > 0 and count > 0:
                left[i] = left[i - 1] + count
            if boxes[i] == '1':
                count += 1
        
        count = 0
        for i in range(n - 1, -1, -1):
            if i < n - 1 and count > 0:
                right[i] = right[i + 1] + count
            if boxes[i] == '1':
                count += 1
        
        for i in range(0, n):
            right[i] += left[i]
        return right

class TestMinimumNumberOfOperationsToMoveAllBallsToEachBox(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        boxes = "110"
        expected = [1, 1, 3]
        self.assertEqual(self.solution.minOperations(boxes), expected)

    def test_example2(self):
        boxes = "001011"
        expected = [11, 8, 5, 4, 3, 4]
        self.assertEqual(self.solution.minOperations(boxes), expected)

    def test_single_box_with_ball(self):
        boxes = "1"
        expected = [0]
        self.assertEqual(self.solution.minOperations(boxes), expected)

    def test_single_box_without_ball(self):
        boxes = "0"
        expected = [0]
        self.assertEqual(self.solution.minOperations(boxes), expected)

if __name__ == "__main__":
    unittest.main()