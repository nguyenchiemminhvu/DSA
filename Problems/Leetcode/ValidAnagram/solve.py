import unittest

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        fs = [0] * 128
        for c in s:
            fs[ord(c)] += 1
        for c in t:
            fs[ord(c)] -= 1
        return all(f == 0 for f in fs)

class TestValidAnagram(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_examples(self):
        self.assertTrue(self.solution.isAnagram("anagram", "nagaram"))
        self.assertFalse(self.solution.isAnagram("rat", "car"))

    def test_edge_cases(self):
        self.assertTrue(self.solution.isAnagram("", ""))
        self.assertFalse(self.solution.isAnagram("a", "b"))
        self.assertTrue(self.solution.isAnagram("aabbcc", "abcabc"))
        self.assertFalse(self.solution.isAnagram("aabbcc", "abccbaaa"))

if __name__ == "__main__":
    unittest.main()