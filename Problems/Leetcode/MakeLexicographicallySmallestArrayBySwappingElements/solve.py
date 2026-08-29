from collections import deque
from typing import List

class Solution:
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:
        nums.append(float('inf'))
        n = len(nums)

        sorted_nums = [(val, i) for i, val in enumerate(nums)]
        sorted_nums.sort()

        group_values = deque([sorted_nums[0][0]])
        group_indices = [sorted_nums[0][1]]
        for i in range(1, n):
            diff = sorted_nums[i][0] - sorted_nums[i - 1][0]
            if diff > limit:
                group_indices.sort()
                for idx in group_indices:
                    nums[idx] = group_values.popleft()
                
                group_indices.clear()
            
            group_values.append(sorted_nums[i][0])
            group_indices.append(sorted_nums[i][1])
        
        return nums[:-1]