class Solution:
    def residuePrefixes(self, s: str) -> int:
        count = 0
        ss = set()
        for i, c in enumerate(s):
            ss.add(c)
            if len(ss) == (i + 1) % 3:
                count += 1
        return count