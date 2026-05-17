class Solution:
    def numSplits(self, s: str) -> int:
        n = len(s)
        left, right = {}, {}
        for c in s:
            right[c] = right.get(c, 0) + 1
        
        res = 0
        for c in s:
            left[c] = left.get(c, 0) + 1
            right[c] -= 1
            if right[c] <= 0:
                right.pop(c)
            if len(left) == len(right):
                res += 1
        return res