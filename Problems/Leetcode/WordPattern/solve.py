import unittest

class Solution:
    def wordPattern(self, pattern: str, s: str) -> bool:
        words = s.split()
        dp = {}
        ds = {}
        if len(pattern) != len(words):
            return False
        
        n = len(pattern)
        for i in range(0, n):
            if pattern[i] in dp and words[i] in ds:
                if dp[pattern[i]] != words[i] or ds[words[i]] != pattern[i]:
                    return False
            else:
                if pattern[i] not in dp and words[i] not in ds:
                    dp[pattern[i]] = words[i]
                    ds[words[i]] = pattern[i]
                else:
                    return False
        return True

class TestWordPattern(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        pattern = "abba"
        s = "dog cat cat dog"
        self.assertTrue(self.solution.wordPattern(pattern, s))

    def test_case_2(self):
        pattern = "abba"
        s = "dog cat cat fish"
        self.assertFalse(self.solution.wordPattern(pattern, s))

    def test_case_3(self):
        pattern = "aaaa"
        s = "dog cat cat dog"
        self.assertFalse(self.solution.wordPattern(pattern, s))

    def test_case_4(self):
        pattern = "abba"
        s = "dog dog dog dog"
        self.assertFalse(self.solution.wordPattern(pattern, s))

    def test_case_5(self):
        pattern = "abc"
        s = "b c a"
        self.assertTrue(self.solution.wordPattern(pattern, s))

if __name__ == "__main__":
    unittest.main()