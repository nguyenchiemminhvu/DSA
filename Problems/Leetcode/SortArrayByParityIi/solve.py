from typing import List

class Solution:
    def sortArrayByParityII(self, nums: List[int]) -> List[int]:
        n = len(nums)
        upper_left = 0
        upper_right = n - 1
        for i in range(n):
            if nums[i] & 1:
                nums[upper_right] = (nums[upper_right] & 0xFFFF) | ((nums[i] & 0xFFFF) << 16)
                upper_right -= 1
            else:
                nums[upper_left] = (nums[upper_left] & 0xFFFF) | ((nums[i] & 0xFFFF) << 16)
                upper_left += 1
        
        upper_left -= 1
        upper_right += 1
        for i in range(n):
            if i & 1:
                nums[i] = (nums[i] & 0xFFFF0000) | ((nums[upper_right] & 0xFFFF0000) >> 16)
                upper_right += 1
            else:
                nums[i] = (nums[i] & 0xFFFF0000) | ((nums[upper_left] & 0xFFFF0000) >> 16)
                upper_left -= 1

        for i in range(n):
            nums[i] = nums[i] & 0xFFFF
        
        return nums