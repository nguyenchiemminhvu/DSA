from typing import List

class Solution:
    def findAndReplacePattern(self, words: List[str], pattern: str) -> List[str]:
        def is_isomorphic(s:str, t:str) -> bool:
            ns, nt = len(s), len(s)
            if ns != nt:
                return False
            
            ds, dt = {}, {}
            for i in range(ns):
                cs, ct = s[i], t[i]
                if cs in ds and ds[cs] != ct:
                    return False
                if ct in dt and dt[ct] != cs:
                    return False
                ds[cs] = ct
                dt[ct] = cs
            
            return True
        
        res = []
        for word in words:
            if is_isomorphic(word, pattern):
                res.append(word)
        return res