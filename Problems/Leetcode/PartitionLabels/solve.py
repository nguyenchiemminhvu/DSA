from typing import List

class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        last = {} # char -> last index
        for i, c in enumerate(s):
            last[c] = i
        
        i = 0
        n = len(s)
        res = []
        sum_res = 0
        while i < n:
            last_idx = last[s[i]]
            j = i
            while j <= last_idx:
                last_idx = max(last_idx, last[s[j]])
                j += 1
            res.append(last_idx - sum_res + 1)
            sum_res += res[-1]
            i = last_idx + 1
        return res