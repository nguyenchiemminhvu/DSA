import unittest

class Solution:
    def longestPalindrome(self, s: str) -> int:
        freq = [0] * 128
        for c in s:
            freq[ord(c)] += 1
        freq.sort(reverse=True)
        
        longest = 0
        s = 0
        for val in freq:
            longest += (val - (val & 1))
            s += val
        return longest + (1 if s > longest else 0)

class TestLongestPalindrome(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        self.assertEqual(self.solution.longestPalindrome("abccccdd"), 7)

    def test_example2(self):
        self.assertEqual(self.solution.longestPalindrome("a"), 1)

    def test_example3(self):
        self.assertEqual(self.solution.longestPalindrome("bb"), 2)

    def test_empty_string(self):
        self.assertEqual(self.solution.longestPalindrome(""), 0)

    def test_all_unique_characters(self):
        self.assertEqual(self.solution.longestPalindrome("abcdef"), 1)

    def test_all_same_characters(self):
        self.assertEqual(self.solution.longestPalindrome("aaaaaa"), 6)

    def test_mixed_characters(self):
        self.assertEqual(self.solution.longestPalindrome("AaBbCc"), 1)

if __name__ == "__main__":
    unittest.main()