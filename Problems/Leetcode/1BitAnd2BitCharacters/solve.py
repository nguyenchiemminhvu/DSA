from typing import List

class Solution:
    def isOneBitCharacter(self, bits: List[int]) -> bool:
        if bits[-1] == 1:
            return False
        
        n = len(bits)
        def check(i: int) -> bool:
            if i == n - 1 and bits[i] == 0:
                return True
            if i >= n:
                return False
            
            if bits[i] == 0:
                return check(i + 1)
            return check(i + 2)
        
        return check(0)