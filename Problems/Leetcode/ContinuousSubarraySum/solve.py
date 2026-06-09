from typing import List

class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        s = 0
        mp = {0: -1}
        for i, val in enumerate(nums):
            s += val
            rem = s % k
            if rem in mp:
                if i - mp[rem] >= 2:
                    return True
            else:
                mp[rem] = i
        
        return False