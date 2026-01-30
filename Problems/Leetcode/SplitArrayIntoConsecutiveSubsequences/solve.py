from typing import List

class Solution:
    def isPossible(self, nums: List[int]) -> bool:
        freq = {}
        need = {}
        for val in nums:
            freq[val] = freq.get(val, 0) + 1
        
        for val in nums:
            if freq.get(val, 0) == 0:
                continue
            if need.get(val, 0) > 0:
                need[val] -= 1
                freq[val] -= 1
                need[val + 1] = need.get(val + 1, 0) + 1
            else:
                if freq.get(val + 1, 0) == 0 or freq.get(val + 2, 0) == 0:
                    return False
                need[val + 3] = need.get(val + 3, 0) + 1
                freq[val] -= 1
                freq[val + 1] -= 1
                freq[val + 2] -= 1
        
        return True