import unittest

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        checker = set()
        n = len(s)
        left = 0
        right = 0
        longest = 0
        while right < n:
            if s[right] not in checker:
                longest = max(longest, right - left + 1)
            else:
                while s[right] in checker:
                    checker.remove(s[left])
                    left += 1
            checker.add(s[right])
            right += 1
                
        return longest

class TestLongestSubstringWithoutRepeatingCharacters(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        s = "abcabcbb"
        expected = 3
        self.assertEqual(self.solution.lengthOfLongestSubstring(s), expected)

    def test_example2(self):
        s = "bbbbb"
        expected = 1
        self.assertEqual(self.solution.lengthOfLongestSubstring(s), expected)

    def test_example3(self):
        s = "pwwkew"
        expected = 3
        self.assertEqual(self.solution.lengthOfLongestSubstring(s), expected)

    def test_empty_string(self):
        s = ""
        expected = 0
        self.assertEqual(self.solution.lengthOfLongestSubstring(s), expected)

    def test_single_character(self):
        s = "a"
        expected = 1
        self.assertEqual(self.solution.lengthOfLongestSubstring(s), expected)

    def test_all_unique_characters(self):
        s = "abcdef"
        expected = 6
        self.assertEqual(self.solution.lengthOfLongestSubstring(s), expected)

    def test_repeating_characters_at_ends(self):
        s = "abcaefghijka"
        expected = 10
        self.assertEqual(self.solution.lengthOfLongestSubstring(s), expected)

if __name__ == "__main__":
    unittest.main()