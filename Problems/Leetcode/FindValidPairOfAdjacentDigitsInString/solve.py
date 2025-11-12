from collections import Counter

class Solution:
    def findValidPair(self, s: str) -> str:
        res = ""
        f = Counter(list(s))
        for i in range(1, len(s)):
            a, b = s[i-1], s[i]
            if a != b and int(a) == f[a] and int(b) == f[b]:
                return s[i-1:i+1]
        return res