from collections import defaultdict

class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        n = len(s)

        mp = defaultdict(int)
        l = 0
        max_freq = 0
        res = 0

        for r in range(n):
            mp[s[r]] += 1
            max_freq = max(max_freq, mp[s[r]])
            
            while (r - l + 1) - max_freq > k:
                mp[s[l]] -= 1
                l += 1

            res = max(res, r - l + 1)

        return res