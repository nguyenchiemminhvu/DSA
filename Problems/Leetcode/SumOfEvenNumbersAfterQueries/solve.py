from typing import List

class Solution:
    def sumEvenAfterQueries(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        res = []
        s = sum(val for val in nums if val % 2 == 0)
        for val, idx in queries:
            cur = nums[idx]
            odd1 = nums[idx] & 1
            nums[idx] += val
            odd2 = nums[idx] & 1
            
            if not odd1 and not odd2:
                s += val
            elif not odd1 and odd2:
                s -= cur
            elif odd1 and not odd2:
                s += nums[idx]
            
            res.append(s)
        
        return res