from typing import List
from collections import defaultdict

class Solution:
    def canArrange(self, arr: List[int], k: int) -> bool:
        freq = defaultdict(int)
        for val in arr:
            rem = (((val % k) + k) % k)
            freq[rem] += 1
        
        if freq[0] & 1:
            return False
        
        for i in range(1, k):
            if freq[i] != freq[k - i]:
                return False
        
        return True