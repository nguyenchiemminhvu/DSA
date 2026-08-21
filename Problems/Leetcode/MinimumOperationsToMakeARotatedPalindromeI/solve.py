class Solution:
    def minOperations(self, s: str) -> int:
        n = len(s)
        s += s
        n2 = len(s)
        res = float('inf')
        for i in range(n - 1, n2):
            # rotate i-th time
            temp = s[i - n + 1:i + 1]
            op = i - n + 1

            l, r = 0, n - 1
            while l < r:
                l_val = ord(temp[l]) - ord('a')
                r_val = ord(temp[r]) - ord('a')
                min_diff = min(abs(r_val - l_val), 26 - abs(r_val - l_val))
                op += min_diff
                l += 1
                r -= 1
            res = min(res, op)
        
        return res