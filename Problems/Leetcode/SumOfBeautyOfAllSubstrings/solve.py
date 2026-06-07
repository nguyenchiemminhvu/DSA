from typing import List, Optional, Tuple

class Solution:
    def beautySum(self, s: str) -> int:
        n = len(s)

        prefix_freq = [[0] * 26]
        f = [0] * 26
        for i in range(n):
            f[ord(s[i]) - ord('a')] += 1
            prefix_freq.append(f[:])
        
        res = 0
        for l in range(n):
            for r in range(l, n):
                f = prefix_freq[r + 1][:]
                for i in range(26):
                    f[i] -= prefix_freq[l][i]
                
                mi, ma = n, 0
                for i in range(26):
                    if f[i]:
                        mi = min(mi, f[i])
                        ma = max(ma, f[i])
                res += ma - mi
        return res