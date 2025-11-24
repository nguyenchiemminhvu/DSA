class Solution:
    def maximumLengthSubstring(self, s: str) -> int:
        n = len(s)
        l, r = 0, 0
        f = {}
        res = 0
        while r < n:
            f[s[r]] = f.get(s[r], 0) + 1
            while any(v > 2 for k, v in f.items()):
                f[s[l]] -= 1
                if f[s[l]] <= 0:
                    f.pop(s[l])
                l += 1
            
            res = max(res, r - l + 1)
            r += 1
        return res
