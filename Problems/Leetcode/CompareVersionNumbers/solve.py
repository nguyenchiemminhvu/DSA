import unittest

class Solution:
    def compareVersion(self, version1: str, version2: str) -> int:
        L1 = list(map(lambda s: int(s), version1.split('.')))
        L2 = list(map(lambda s: int(s), version2.split('.')))
        if (len(L1) < len(L2)):
            L1 += [0] * (len(L2) - len(L1))
        if (len(L1) > len(L2)):
            L2 += [0] * (len(L1) - len(L2))
        
        for i in range(0, len(L1)):
            if (L1[i] < L2[i]):
                return -1
            if (L1[i] > L2[i]):
                return 1
        return 0

class TestCompareVersionNumbers(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

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