from collections import Counter

class Solution:
    def equalFrequency(self, word: str) -> bool:
        for i in range(len(word)):
            sub = word[0:i] + word[i + 1:]
            f = Counter(list(sub))
            if min(f.values()) == max(f.values()):
                return True
        return False