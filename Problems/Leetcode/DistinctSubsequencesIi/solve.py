from collections import defaultdict
import string

class Solution:
    def distinctSubseqII(self, s: str) -> int:
        n = len(s)
        mod = 10 ** 9 + 7

        end_with = defaultdict(int)
        for c in s:
            val = 0
            for it in string.ascii_lowercase:
                val = ((val % mod) + (end_with[it] % mod)) % mod
            end_with[c] = (val + 1) % mod
        
        res = 0
        for c, count in end_with.items():
            res = ((res % mod) + (count % mod)) % mod
        return res