from typing import Dict, Tuple

class Solution:
    def rearrangeSticks(self, n: int, k: int) -> int:
        mod = 10**9 + 7
        mem = {}
        def F(i: int, k: int) -> int:
            if i == 0 and k == 0:
                return 1
            if k == 0:
                return 0
            if k > i:
                return 0
            
            if (i, k) in mem:
                return mem[(i, k)]
            
            opt1 = F(i - 1, k - 1) # ways to put the smallest one to the left
            opt2 = (i - 1) * F(i - 1, k) # ways to put smallest one any where in (n-1) other index
            res = (opt1 + opt2) % mod
            mem[(i, k)] = res
            return res
        
        return F(n, k)