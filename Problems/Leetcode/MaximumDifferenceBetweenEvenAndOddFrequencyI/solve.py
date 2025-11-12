from collections import Counter

class Solution:
    def maxDifference(self, s: str) -> int:
        f = Counter(list(s))
        odd = max(val for val in f.values() if val & 1)
        even = min(val for val in f.values() if val % 2 == 0)
        return odd - even