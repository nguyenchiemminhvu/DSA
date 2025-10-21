class Solution:
    def makeSmallestPalindrome(self, s: str) -> str:
        n = len(s)
        left = right = n // 2
        if not (n & 1):
            left -= 1
        
        s = list(s)
        while left >= 0 and right < n:
            if s[left] != s[right]:
                s[left] = s[right] = min(s[left], s[right])
            left -= 1
            right += 1
        return "".join(s)