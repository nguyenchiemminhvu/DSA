import string
from typing import List

class Solution:
    def commonChars(self, words: List[str]) -> List[str]:
        f = [dict() for _ in range(26)]
        n = len(words)
        for i in range(n):
            for c in words[i]:
                idx = ord(c) - ord('a')
                f[idx][i] = f[idx].get(i, 0) + 1

        res = []
        for idx in range(26):
            c = chr(ord('a') + idx)
            if len(f[idx].keys()) == n:
                res.extend([c] * min(f[idx].values()))
        return res