import unittest

class Solution:
    def removeOccurrences(self, s: str, part: str) -> str:
        found_idx = -1
        while len(s) > 0 and (found_idx := s.find(part)) != -1:
            s = s[:found_idx] + s[found_idx + len(part):]
        return s

class TestRemoveAllOccurrencesOfASubString(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        s = "daabcbaabcbc"
        part = "abc"
        expected = "dab"
        self.assertEqual(self.solution.removeOccurrences(s, part), expected)

    def test_example2(self):
        s = "axxxxyyyyb"
        part = "xy"
        expected = "ab"
        self.assertEqual(self.solution.removeOccurrences(s, part), expected)

if __name__ == "__main__":
    unittest.main()