class Solution:
    def longestPrefix(self, s: str) -> str:
        n = len(s)
        for i in range(1, n):
            if s.startswith(s[i:]):
                return s[i:]
        return ''