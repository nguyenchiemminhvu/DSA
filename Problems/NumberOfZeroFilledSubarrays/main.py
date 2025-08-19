# https://leetcode.com/problems/number-of-zero-filled-subarrays/

class Solution:
    def zeroFilledSubarray(self, nums: List[int]) -> int:
        res = 0
        nums.append(1)
        n = len(nums)
        count_zero = 0
        for i in range(0, n):
            if (nums[i] == 0):
                count_zero += 1
            else:
                res += int((count_zero * (count_zero + 1)) / 2)
                count_zero = 0
        
        return res