# https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii

from typing import List

class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        n = len(nums)
        max_left = [float('-inf')] * n
        max_right = [float('-inf')] * n
        for i in range(1, n):
            max_left[i] = max(max_left[i - 1], nums[i - 1])
        for i in range(n - 2, -1, -1):
            max_right[i] = max(max_right[i + 1], nums[i + 1])
        
        res = 0
        for i in range(1, n-1):
            if (max_left[i] > nums[i]):
                res = max(res, (max_left[i] - nums[i]) * max_right[i])
        return res

if __name__ == "__main__":
    nums = [12,6,1,2,7]
    sol = Solution()
    print(sol.maximumTripletValue(nums)) # Output: 6
    
    nums = [1,10,3,4,19]
    sol = Solution()
    print(sol.maximumTripletValue(nums)) # Output: 7
