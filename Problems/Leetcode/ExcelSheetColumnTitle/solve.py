import unittest

class Solution:
    def convertToTitle(self, n: int) -> str:
        table = []
        while n:
            n -= 1
            table.append(n % 26)
            n //= 26
        table.reverse()
        return "".join([chr(ord('A') + val) for val in table])

class TestExcelSheetColumnTitle(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        self.assertEqual(self.solution.convertToTitle(1), "A")

    def test_example2(self):
        self.assertEqual(self.solution.convertToTitle(28), "AB")

    def test_example3(self):
        self.assertEqual(self.solution.convertToTitle(701), "ZY")

    def test_additional1(self):
        self.assertEqual(self.solution.convertToTitle(52), "AZ")

    def test_additional2(self):
        self.assertEqual(self.solution.convertToTitle(703), "AAA")

if __name__ == "__main__":
    unittest.main()