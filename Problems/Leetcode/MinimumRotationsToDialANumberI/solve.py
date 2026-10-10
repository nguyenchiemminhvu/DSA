class Solution:
    def minRotations(self, s: str) -> int:
        res = 0
        cur = 0
        for c in s:
            next_val = int(ord(c) - ord('0'))
            diff = abs(next_val - cur)
            res += min(diff, 10 - diff)
            cur = next_val        
        return res