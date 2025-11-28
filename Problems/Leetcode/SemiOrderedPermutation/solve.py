from typing import List

class Solution:
    def semiOrderedPermutation(self, nums: List[int]) -> int:
        n = len(nums)
        count = 0
        mi = min(nums)
        mi_idx = nums.index(mi)
        while mi_idx != 0:
            nums[mi_idx], nums[mi_idx - 1] = nums[mi_idx - 1], nums[mi_idx]
            mi_idx -= 1
            count += 1
        
        ma = max(nums)
        ma_idx = nums.index(ma)
        while ma_idx != n - 1:
            nums[ma_idx], nums[ma_idx + 1] = nums[ma_idx + 1], nums[ma_idx]
            ma_idx += 1
            count += 1
        
        return count