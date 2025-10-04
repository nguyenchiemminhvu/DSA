import unittest

class Solution:
    def reverse(self, x: int) -> int:
        digits = abs(x)
        r = 0
        while digits:
            r = r * 10 + (digits % 10)
            digits //= 10
        
        if r > 0x7FFFFFFF:
            return 0
        return r if x > 0 else -r

class TestReverseInteger(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        self.assertEqual(self.solution.reverse(123), 321)

    def test_example2(self):
        self.assertEqual(self.solution.reverse(-123), -321)

    def test_example3(self):
        self.assertEqual(self.solution.reverse(120), 21)

    def test_example4(self):
        self.assertEqual(self.solution.reverse(0), 0)

    def test_overflow(self):
        self.assertEqual(self.solution.reverse(1534236469), 0)

if __name__ == "__main__":
    unittest.main()