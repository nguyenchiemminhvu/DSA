from typing import Dict
import unittest

class Solution:
    def isIsomorphic(self, s: str, t: str) -> bool:
        sd : Dict[str, str] = {}
        td : Dict[str, str] = {}
        for i in range(len(s)):
            if s[i] in sd and sd[s[i]] != t[i]:
                return False
            if t[i] in td and td[t[i]] != s[i]:
                return False
            sd[s[i]] = t[i]
            td[t[i]] = s[i]
        return True

class TestIsomorphicStrings(unittest.TestCase):
    def setUp(self):
        self.solution = Solution()

    def test_isomorphic_strings(self):
        self.assertTrue(self.solution.isIsomorphic("egg", "add"))
        self.assertFalse(self.solution.isIsomorphic("foo", "bar"))
        self.assertTrue(self.solution.isIsomorphic("paper", "title"))
        self.assertFalse(self.solution.isIsomorphic("ab", "aa"))

if __name__ == "__main__":
    unittest.main()