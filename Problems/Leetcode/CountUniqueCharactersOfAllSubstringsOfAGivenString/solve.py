from collections import defaultdict
import string

class Solution:
    def uniqueLetterString(self, s: str) -> int:
        n = len(s)
        mp = defaultdict(list)
        for i, c in enumerate(s):
            mp[c].append(i)
        
        res = 0
        for c in string.ascii_uppercase:
            arr = [-1] + mp[c] + [n]
            for i in range(1, len(arr) - 1):
                res += (arr[i] - arr[i - 1]) * (arr[i + 1] - arr[i])
        
        return res