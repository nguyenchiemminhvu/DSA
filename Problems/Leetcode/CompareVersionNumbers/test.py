import unittest
import solve

class TestCompareVersionNumbers(unittest.TestCase):
    def setUp(self):
        self.solution = solve.Solution()

    def test_case_1(self):
        version1 = "1.01"
        version2 = "1.001"
        expected = 0
        self.assertEqual(self.solution.compareVersion(version1, version2), expected)

    def test_case_2(self):
        version1 = "1.0"
        version2 = "1.0.0"
        expected = 0
        self.assertEqual(self.solution.compareVersion(version1, version2), expected)

    def test_case_3(self):
        version1 = "0.1"
        version2 = "1.1"
        expected = -1
        self.assertEqual(self.solution.compareVersion(version1, version2), expected)

    def test_case_4(self):
        version1 = "1.0.1"
        version2 = "1"
        expected = 1
        self.assertEqual(self.solution.compareVersion(version1, version2), expected)

if __name__ == '__main__':
    unittest.main()