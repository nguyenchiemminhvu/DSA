from typing import List
from collections import deque

class Solution:
    def lastVisitedIntegers(self, nums: List[int]) -> List[int]:
        q = deque()
        ans = []
        neg_idx = 0
        for i in range(len(nums)):
            if nums[i] > 0:
                q.appendleft(nums[i])
                neg_idx = 0
            else:
                if neg_idx < len(q):
                    ans.append(q[neg_idx])
                else:
                    ans.append(-1)
                neg_idx += 1
        return ans