from collections import defaultdict

class Solution:
    def canConstruct(self, s: str, k: int) -> bool:
        if k > len(s):
            return False
        
        f = defaultdict(int)
        for c in s:
            f[c] += 1
        
        count_odd_freq = 0
        for c in f:
            count_odd_freq += (f[c] & 1)
        
        return count_odd_freq <= k