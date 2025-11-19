class Solution:
    def largestGoodInteger(self, s: str) -> str:
        count = 0
        prev = '#'
        candidates = []
        for c in s:
            if c == prev:
                count += 1
                if count == 3:
                    candidates.append(c * 3)
            else:
                count = 1
            prev = c
        return "" if not candidates else max(candidates)