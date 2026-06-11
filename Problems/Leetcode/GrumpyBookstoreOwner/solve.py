from typing import List

class Solution:
    def maxSatisfied(self, customers: List[int], grumpy: List[int], k: int) -> int:
        n = len(customers)

        total = sum(val for i, val in enumerate(customers) if grumpy[i] == 0)

        res = total
        l = 0
        additional = 0
        for r in range(n):
            if grumpy[r] == 1:
                additional += customers[r]
            
            while r - l + 1 > k:
                if grumpy[l] == 1:
                    additional -= customers[l]
                l += 1
            
            res = max(res, total + additional)
        
        return res