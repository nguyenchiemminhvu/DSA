from typing import List

class Solution:
    def validStrings(self, n: int) -> List[str]:
        def valid(val:int) -> bool:
            for i in range(1, n):
                if (val & 0b11) == 0:
                    return False
                val >>= 1
            return True
        
        res = []
        total = (1 << n)
        for t in range(total):
            mask = t
            if valid(mask):
                s = []
                for i in range(n):
                    s.append(int(((1 << i) & mask) > 0))
                    s[-1] = str(s[-1])
                s.reverse()
                res.append("".join(s))

        return res