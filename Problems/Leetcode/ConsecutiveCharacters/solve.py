class Solution:
    def maxPower(self, s: str) -> int:
        res = 1
        count, prev = 1, '#'
        for c in s:
            if c == prev:
                count += 1
                res = max(res, count)
            else:
                count = 1
            prev = c
        return res