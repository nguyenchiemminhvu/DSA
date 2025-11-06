import string

class Solution:
    def sortString(self, s: str) -> str:
        f = {}
        for c in s:
            f[c] = f.get(c, 0) + 1
        
        n = len(s)
        res = ""
        while len(res) < n:
            for c in string.ascii_lowercase:
                if c in f and f[c] > 0:
                    res += c
                    f[c] -= 1
            for c in string.ascii_lowercase[::-1]:
                if c in f and f[c] > 0:
                    res += c
                    f[c] -= 1
        return res