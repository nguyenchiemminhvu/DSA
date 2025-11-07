from typing import defaultdict

class Solution:
    def rearrangeCharacters(self, s: str, target: str) -> int:
        ft = defaultdict(int)
        for c in target:
            ft[c] += 1
        
        fs = defaultdict(int)
        for c in s:
            fs[c] += 1
        
        res = len(s)
        for c in set(list(target)):
            res = min(res, fs[c] // ft[c])
        return res