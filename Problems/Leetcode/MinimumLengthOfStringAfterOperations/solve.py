from collections import defaultdict

class Solution:
    def minimumLength(self, s: str) -> int:
        f = defaultdict(int)
        for c in s:
            f[c] += 1
        
        res = len(s)
        for c in f:
            if f[c] >= 3:
                if f[c] & 1:
                    res -= (f[c] - 1)
                else:
                    res -= (f[c] - 2)
        return res