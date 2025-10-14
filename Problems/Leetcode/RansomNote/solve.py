import unittest

class Solution:
    def canConstruct(self, s: str, t: str) -> bool:
        f = [0] * 128
        for c in t:
            f[ord(c)] += 1
        for c in s:
            f[ord(c)] -= 1
            if f[ord(c)] < 0:
                return False
        return True

class TestRansomNote(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_canConstruct(self):
        self.assertFalse(self.solution.canConstruct("a", "b"))
        self.assertFalse(self.solution.canConstruct("aa", "ab"))
        self.assertTrue(self.solution.canConstruct("aa", "aab"))
        self.assertTrue(self.solution.canConstruct("", "aab"))
        self.assertFalse(self.solution.canConstruct("a", ""))

if __name__ == "__main__":
    unittest.main()