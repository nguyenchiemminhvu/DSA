class Solution:
    def isPrefixOfWord(self, s: str, t: str) -> int:
        words = s.split()
        for i, word in enumerate(words):
            if word.startswith(t):
                return i + 1
        return -1