class Solution:
    def findPermutationDifference(self, s: str, t: str) -> int:
        ds = {}
        dt = {}
        for i, c in enumerate(s):
            ds[c] = i
        for i, c in enumerate(t):
            dt[c] = i
        res = 0
        for i in range(len(s)):
            res += abs(ds[s[i]] - dt[s[i]])
        return res