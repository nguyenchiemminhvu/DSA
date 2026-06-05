from typing import List

class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        fp = [0] * 26
        for c in p:
            fp[ord(c) - ord('a')] += 1
        
        ns, np = len(s), len(p)

        res = []
        fs = [0] * 26
        l = 0
        for r in range(ns):
            fs[ord(s[r]) - ord('a')] += 1

            if r - l + 1 > np:
                fs[ord(s[l]) - ord('a')] -= 1
                l += 1
            
            if r - l + 1 == np:
                if fp == fs:
                    res.append(l)
        
        return res