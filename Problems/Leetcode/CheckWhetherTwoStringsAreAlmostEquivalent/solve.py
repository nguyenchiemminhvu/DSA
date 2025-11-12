import string
from collections import Counter

class Solution:
    def checkAlmostEquivalent(self, word1: str, word2: str) -> bool:
        f1 = Counter(list(word1))
        f2 = Counter(list(word2))
        for c in string.ascii_lowercase:
            if abs(f1[c] - f2[c]) > 3:
                return False
        return True