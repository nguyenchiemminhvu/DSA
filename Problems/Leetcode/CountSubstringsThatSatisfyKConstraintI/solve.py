class Solution:
    def countKConstraintSubstrings(self, s: str, k: int) -> int:
        n = len(s)
        res = 0
        for i in range(n):
            c0, c1 = 0, 0
            for j in range(i, n):
                c0 += int(s[j] == '0')
                c1 += int(s[j] == '1')
                if c0 > k and c1 > k:
                    break
                res += 1
        return res