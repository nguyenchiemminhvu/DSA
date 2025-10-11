import unittest

class Solution:
    def countBinarySubstrings(self, s: str) -> int:
        count = 0
        s += '2'
        n = len(s)
        counter = [0] * 3
        prev = s[0]
        for val in s:
            if val != prev:
                count += min(counter[0], counter[1])
                counter[ord(val) - ord('0')] = 0
                prev = val
            counter[ord(val) - ord('0')] += 1
        return count

class TestCountBinarySubstrings(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        s = "00110011"
        expected = 6
        self.assertEqual(self.solution.countBinarySubstrings(s), expected)

    def test_case_2(self):
        s = "10101"
        expected = 4
        self.assertEqual(self.solution.countBinarySubstrings(s), expected)

    def test_case_3(self):
        s = "000111"
        expected = 3
        self.assertEqual(self.solution.countBinarySubstrings(s), expected)

    def test_case_4(self):
        s = "0000"
        expected = 0
        self.assertEqual(self.solution.countBinarySubstrings(s), expected)

    def test_case_5(self):
        s = "01"
        expected = 1
        self.assertEqual(self.solution.countBinarySubstrings(s), expected)

if __name__ == "__main__":
    unittest.main()