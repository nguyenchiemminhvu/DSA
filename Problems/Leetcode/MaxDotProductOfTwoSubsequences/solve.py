from typing import List

class Solution:
    def maxDotProduct(self, a1: List[int], a2: List[int]) -> int:
        n1 = len(a1)
        n2 = len(a2)
        memo = {}

        # F(i1, i2) -> max dot product of subsequences a1[:i1+1] and a2[:i2+1]
        def F(i1:int, i2:int) -> int:
            if i1 < 0 or i2 < 0:
                return float('-inf')
            if (i1, i2) in memo:
                return memo[(i1, i2)]
            
            cur_prod = a1[i1] * a2[i2]
            max_so_far = max([cur_prod, cur_prod + F(i1 - 1, i2 - 1), F(i1 - 1, i2), F(i1, i2 - 1)])
            
            memo[(i1, i2)] = max_so_far
            return max_so_far
        
        return F(n1 - 1, n2 - 1)