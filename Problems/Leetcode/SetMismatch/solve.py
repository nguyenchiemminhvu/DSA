from typing import List

class Solution:
    def findErrorNums(self, nums: List[int]) -> List[int]:
        n = len(nums)
        expected_sum = n * (n + 1) // 2
        cur_sum = sum(nums)
        non_dup_sum = sum(set(nums))
        dup_val = cur_sum - non_dup_sum
        mis_val = expected_sum - cur_sum + dup_val
        return [dup_val, mis_val]