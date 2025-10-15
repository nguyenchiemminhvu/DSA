class Solution:
    def minimumMoves(self, s: str) -> int:
        i = 0
        n = len(s)
        count = 0
        while i < n:
            if s[i] == 'X':
                count += 1
                i += 2
            i += 1
        return count