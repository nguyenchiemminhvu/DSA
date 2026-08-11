from collections import defaultdict

class Solution:
    def sortVowels(self, s: str) -> str:
        s = list(s)

        vowels = set(list('aeiou'))
        indices = []
        f = defaultdict(int)
        first = defaultdict(lambda: float('inf'))

        for i, c in enumerate(s):
            if c in vowels:
                indices.append(i)
                first[c] = min(first[c], i)
                f[c] += 1
        
        arr = ['a', 'e', 'i', 'o', 'u']
        arr.sort(key=lambda x: (-f[x], first[x]))

        temp_s = []
        for c in arr:
            temp_s.extend(c * f[c])
        
        for i in range(len(indices)):
            s[indices[i]] = temp_s[i]
        
        return ''.join(s)