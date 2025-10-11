import unittest

class Solution:
    def titleToNumber(self, title: str) -> int:
        title = title[::-1]
        val = 0
        for i, c in enumerate(title):
            val += 26 ** i * (ord(c) - ord('A') + 1)
        return val

class TestExcelSheetColumnNumber(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        self.assertEqual(self.solution.titleToNumber("A"), 1)

    def test_example2(self):
        self.assertEqual(self.solution.titleToNumber("AB"), 28)

    def test_example3(self):
        self.assertEqual(self.solution.titleToNumber("ZY"), 701)

    def test_single_letter(self):
        self.assertEqual(self.solution.titleToNumber("Z"), 26)

    def test_long_title(self):
        self.assertEqual(self.solution.titleToNumber("AAA"), 703)

    def test_edge_case(self):
        self.assertEqual(self.solution.titleToNumber("ZZZ"), 18278)

if __name__ == "__main__":
    unittest.main()