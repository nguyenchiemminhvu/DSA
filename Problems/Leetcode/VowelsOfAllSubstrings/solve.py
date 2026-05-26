class Solution:
    def countVowels(self, s: str) -> int:
        n = len(s)
        
        def vowel(x):
            return x == 'a' or x == 'e' or x == 'i' or x == 'o' or x == 'u'

        res = 0
        for i, c in enumerate(s):
            if vowel(c):
                res += (i + 1) * (n - i)
        return res