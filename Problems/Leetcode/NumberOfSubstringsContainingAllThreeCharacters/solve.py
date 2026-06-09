from collections import defaultdict

class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        n = len(s)
        
        res = 0
        mp = defaultdict(int)
        l = 0
        for r in range(n):
            mp[s[r]] += 1

            while mp['a'] and mp['b'] and mp['c']:
                res += (n - r)
                mp[s[l]] -= 1
                l += 1
        
        return res