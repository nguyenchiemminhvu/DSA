from collections import Counter

class Solution:
    def closeStrings(self, s1: str, s2: str) -> bool:
        n1 = len(s1)
        n2 = len(s2)
        if n1 != n2:
            return False
        
        ss1 = set(s1)
        ss2 = set(s2)
        if ss1 != ss2:
            return False
        
        f1 = Counter(s1)
        f2 = Counter(s2)

        ff1 = list(f1.values())
        ff2 = list(f2.values())
        ff1.sort()
        ff2.sort()

        return ff1 == ff2