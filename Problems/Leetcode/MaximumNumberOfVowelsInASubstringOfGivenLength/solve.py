class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        def is_vowel(ch: str) -> bool:
            return ch=='a' or ch=='e' or ch=='i' or ch=='o' or ch=='u'
        
        n = len(s)
        l = 0
        count = 0
        res = 0
        for r in range(n):
            count += int(is_vowel(s[r]))
            while r - l > k - 1:
                count -= int(is_vowel(s[l]))
                l += 1
            if r - l == k - 1:
                res = max(res, count)
        return res