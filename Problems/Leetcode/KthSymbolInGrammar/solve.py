import unittest

class Solution:
    def kthGrammar(self, n: int, k: int) -> int:
        if n == 1:
            return 0
               
        prev_len = 2 ** (n - 2)

        if k <= prev_len:
            return self.kthGrammar(n - 1, k)
        else:
            return 1 - self.kthGrammar(n - 1, k - prev_len)

class TestKthSymbolInGrammar(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        self.assertEqual(self.solution.kthGrammar(1, 1), 0)

    def test_example2(self):
        self.assertEqual(self.solution.kthGrammar(2, 1), 0)

    def test_example3(self):
        self.assertEqual(self.solution.kthGrammar(2, 2), 1)

    def test_example4(self):
        self.assertEqual(self.solution.kthGrammar(3, 1), 0)

    def test_example5(self):
        self.assertEqual(self.solution.kthGrammar(3, 2), 1)

if __name__ == "__main__":
    unittest.main()