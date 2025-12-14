from typing import List

class Solution:
    def numberOfWays(self, s: str) -> int:
        n = len(s)
        mod = 10**9 + 7
        total_seats = s.count('S')
        if total_seats == 0 or total_seats & 1:
            return 0
        
        pos = [i for i, c in enumerate(s) if c == 'S']
        res = 1
        for i in range(1, total_seats // 2):
            left_idx = pos[2 * i - 1]
            right_idx = pos[2 * i]
            res = res * (right_idx - left_idx) % mod
        return res