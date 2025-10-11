import unittest

class Solution:
    def isPowerOfFour(self, n: int) -> bool:
        if n & (n - 1) != 0:
            return False
        masks = 0x55555555
        return (n & masks) > 0

class TestPowerOfFour(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_isPowerOfFour(self):
        self.assertTrue(self.solution.isPowerOfFour(16))
        self.assertFalse(self.solution.isPowerOfFour(5))
        self.assertTrue(self.solution.isPowerOfFour(1))
        self.assertFalse(self.solution.isPowerOfFour(0))
        self.assertFalse(self.solution.isPowerOfFour(-4))
        self.assertTrue(self.solution.isPowerOfFour(64))
        self.assertFalse(self.solution.isPowerOfFour(12))

if __name__ == "__main__":
    unittest.main()