import string

class Solution:
    def vowelConsonantScore(self, s: str) -> int:
        vow = 0
        con = 0
        for c in s:
            if c in 'aeiou':
                vow += 1
            elif c in string.ascii_lowercase:
                con += 1
        
        return vow // con if con > 0 else 0