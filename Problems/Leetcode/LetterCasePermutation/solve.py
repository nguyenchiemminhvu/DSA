from typing import List

class Solution:
    def letterCasePermutation(self, s: str) -> List[str]:
        n = len(s)
        res = []
        tmp = []
        def generating(idx: int) -> None:
            if idx >= n:
                res.append("".join(tmp))
                return
            
            c = s[idx]
            if c.isdigit():
                tmp.append(s[idx])
                generating(idx + 1)
                tmp.pop()
            else:
                tmp.append(s[idx].lower())
                generating(idx + 1)
                tmp.pop()

                tmp.append(s[idx].upper())
                generating(idx + 1)
                tmp.pop()
        
        generating(0)
        return res