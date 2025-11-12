from typing import List
from collections import Counter

class Solution:
    def makeEqual(self, words: List[str]) -> bool:
        if len(words) == 1:
            return True

        f = Counter()
        for word in words:
            f += Counter(list(word))
        
        n = len(words)
        return all(v % n == 0 for v in f.values())