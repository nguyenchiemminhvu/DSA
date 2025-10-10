import unittest

class Solution:
    def reverseVowels(self, s: str) -> str:
        vowels = 'AEIOUaeiou'
        s = list(s)
        temp = []
        for i, c in enumerate(s):
            if c in vowels:
                temp.append(i)
        
        left = 0
        right = len(temp) - 1
        while left <= right:
            s[temp[left]], s[temp[right]] = s[temp[right]], s[temp[left]]
            left += 1
            right -= 1
        return "".join(s)

class TestReverseVowelsInAString(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        s = "hello"
        expected = "holle"
        self.assertEqual(self.solution.reverseVowels(s), expected)

    def test_example2(self):
        s = "leetcode"
        expected = "leotcede"
        self.assertEqual(self.solution.reverseVowels(s), expected)

    def test_no_vowels(self):
        s = "rhythm"
        expected = "rhythm"
        self.assertEqual(self.solution.reverseVowels(s), expected)

    def test_all_vowels(self):
        s = "aeiou"
        expected = "uoiea"
        self.assertEqual(self.solution.reverseVowels(s), expected)

    def test_mixed_case(self):
        s = "aA"
        expected = "Aa"
        self.assertEqual(self.solution.reverseVowels(s), expected)

    def test_empty_string(self):
        s = ""
        expected = ""
        self.assertEqual(self.solution.reverseVowels(s), expected)

if __name__ == "__main__":
    unittest.main()