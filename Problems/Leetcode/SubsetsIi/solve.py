from typing import List

class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        nn = (1 << n)
        nums.sort()
        s = set()
        for mask in range(nn):
            tmp = []
            for i in range(32):
                if (1 << i) & mask:
                    tmp.append(nums[i])
            s.add(tuple(tmp))
        return [list(arr) for arr in s]