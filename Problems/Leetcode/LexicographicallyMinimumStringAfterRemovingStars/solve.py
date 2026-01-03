import string

class Solution:
    def clearStars(self, s: str) -> str:
        sts = [[] for i in range(26)]
        for i, c in enumerate(s):
            if c == '*':
                for j in range(26):
                    if sts[j]:
                        sts[j].pop()
                        break
            else:
                st_idx = ord(c) - ord('a')
                sts[st_idx].append(i)
        
        picked_idx = set([idx for st in sts if st for idx in st])
        res = ""
        for i in range(len(s)):
            if i in picked_idx:
                res += s[i]
        return res