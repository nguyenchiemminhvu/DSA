class Solution:
    def isPalindromic(self, s: str) -> bool:
        bs = ''
        for c in s:
            val = bin(ord(c))[2:][-8:].zfill(8)
            bs += val
        
        return bs == bs[::-1]