class Solution:
    def halvesAreAlike(self, s: str) -> bool:
        n = len(s)
        count = 0
        for i in range(n//2):
            if s[i] in 'aeiouAEIOU':
                count += 1
        for i in range(n//2, n):
            if s[i] in 'aeiouAEIOU':
                count -= 1
        return count == 0