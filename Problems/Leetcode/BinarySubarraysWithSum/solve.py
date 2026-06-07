from typing import List

class Solution:
    def numSubarraysWithSum(self, nums: List[int], goal: int) -> int:
        mp = {}
        mp[0] = 1

        res = 0
        cur_sum = 0
        for val in nums:
            cur_sum += val
            if cur_sum - goal in mp:
                res += mp[cur_sum - goal]
            mp[cur_sum] = mp.get(cur_sum, 0) + 1
        return res