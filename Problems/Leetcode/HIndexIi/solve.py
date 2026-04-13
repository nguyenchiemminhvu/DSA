from typing import List

class Solution:
    def hIndex(self, cts: List[int]) -> int:
        n = len(cts)
        left, right = 0, n - 1
        
        while left <= right:
            mid = left + (right - left) // 2
            h = n - mid
            
            if cts[mid] >= h:
                right = mid - 1
            else:
                left = mid + 1
                
        return n - left