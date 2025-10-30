import string

class Solution:
    def maxFreqSum(self, s: str) -> int:
        vowels = set(list('aeiou'))
        max_vow = 0
        max_con = 0
        freq = {}
        for c in s:
            freq[c] = freq.get(c, 0) + 1
        
        for c in list(string.ascii_lowercase):
            if c in vowels:
                max_vow = max(max_vow, freq.get(c, 0))
            else:
                max_con = max(max_con, freq.get(c, 0))
        return max_vow + max_con