from typing import List
from collections import Counter

class Solution:
    def countWords(self, words1: List[str], words2: List[str]) -> int:
        f1 = Counter(words1)
        f2 = Counter(words2)
        res = 0
        for word in words1:
            if f1[word] == 1 and f2[word] == 1:
                res += 1
        return res