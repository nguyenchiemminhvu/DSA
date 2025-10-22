class Solution:
    def minSteps(self, s: str, t: str) -> int:
        f = [0] * 128
        for c in s:
            f[ord(c)] += 1
        for c in t:
            f[ord(c)] -= 1
        
        count = 0
        for val in f:
            count += abs(val)
        return count // 2