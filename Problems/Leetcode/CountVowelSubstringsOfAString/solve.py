from collections import defaultdict

class Solution:
    def countVowelSubstrings(self, word: str) -> int:
        n = len(word)
        l, r = 0, 0
        res = 0
        f = defaultdict(int)
        while r < n:
            if word[r] not in 'aeiou':
                f = defaultdict(int)
                l = r = r + 1
                continue
            
            f[word[r]] += 1
            while all(f[c] > 0 for c in 'aeiou'):
                idx = r
                while idx < n and word[idx] in 'aeiou':
                    res += 1
                    idx += 1
        
                f[word[l]] -= 1
                l += 1
            r += 1
        return res