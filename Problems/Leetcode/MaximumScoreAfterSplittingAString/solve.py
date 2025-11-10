class Solution:
    def maxScore(self, s: str) -> int:
        prefix = [int(val) for val in s]
        s = sum(prefix)
        left = 0
        res = 0
        for i in range(0, len(prefix) - 1):
            left += prefix[i]
            right = s - left
            res = max(res, i + 1 - left + right)
        return res