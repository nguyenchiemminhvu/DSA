import unittest

class Solution:
    def reversePrefix(self, word: str, ch: str) -> str:
        try:
            found = word.index(ch)
        except:
            return word
        
        left = word[:found+1][::-1]
        right = word[found+1:]
        return left + right

class TestReversePrefixOfWord(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_case_1(self):
        word = "abcdefd"
        ch = "d"
        expected = "dcbaefd"
        self.assertEqual(self.solution.reversePrefix(word, ch), expected)

    def test_case_2(self):
        word = "xyxzxe"
        ch = "z"
        expected = "zxyxxe"
        self.assertEqual(self.solution.reversePrefix(word, ch), expected)

    def test_case_3(self):
        word = "abcd"
        ch = "z"
        expected = "abcd"
        self.assertEqual(self.solution.reversePrefix(word, ch), expected)

if __name__ == "__main__":  
    unittest.main()