class Solution:
    def smallestPalindrome(self, s: str) -> str:
        n = len(s)
        mid = None
        if n & 1:
            mid = s[n // 2]
        
        f = [0] * 26
        for c in s:
            f[ord(c) - ord('a')] += 1
        
        res = ''
        for i in range(26):
            if f[i] > 0:
                res += chr(ord('a') + i) * (f[i] // 2)
        return res + (mid if mid else '') + res[::-1]