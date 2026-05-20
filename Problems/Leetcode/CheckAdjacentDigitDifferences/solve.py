class Solution:
    def isAdjacentDiffAtMostTwo(self, s: str) -> bool:
        n = len(s)
        for i in range(1, n):
            a, b = int(s[i - 1]), int(s[i])
            if abs(a - b) > 2:
                return False
        return True