class Solution:
    def possibleStringCount(self, word: str) -> int:
        res = 1
        prev = '#'
        count = 0
        for c in word:
            if c != prev:
                count = 1
            else:
                count += 1
                if count > 1:
                    res += 1
            prev = c
        return res