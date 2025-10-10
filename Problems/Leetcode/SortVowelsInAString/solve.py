import unittest

class Solution:
    def sortVowels(self, s: str) -> str:
        s = list(s)
        vowels = 'AEIOUaeiou'
        counter = [0] * 128

        for c in s:
            if (c in vowels):
                counter[ord(c)] += 1
        
        iv = 0
        for i in range(0, len(s)):
            if s[i] in vowels:
                while iv < len(vowels) and counter[ord(vowels[iv])] <= 0:
                    iv += 1
                s[i] = vowels[iv]
                counter[ord(vowels[iv])] -= 1
        
        return "".join(s)

class TestSortVowelsInAString(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_example1(self):
        s = "lEetcOde"
        expected = "lEOtcede"
        self.assertEqual(self.solution.sortVowels(s), expected)

    def test_example2(self):
        s = "lYmpH"
        expected = "lYmpH"
        self.assertEqual(self.solution.sortVowels(s), expected)

    def test_no_vowels(self):
        s = "bcdfg"
        expected = "bcdfg"
        self.assertEqual(self.solution.sortVowels(s), expected)

    def test_all_vowels(self):
        s = "aeiouAEIOU"
        expected = "AEIOUaeiou"
        self.assertEqual(self.solution.sortVowels(s), expected)

if __name__ == "__main__":
    unittest.main()