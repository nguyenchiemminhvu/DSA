from typing import List

class Solution:
    def maximumNumberOfStringPairs(self, words: List[str]) -> int:
        f = {}
        res = 0
        for word in words:
            rev = word[::-1]
            if rev in f:
                res += f[rev]
            f[word] = f.get(word, 0) + 1
        return res