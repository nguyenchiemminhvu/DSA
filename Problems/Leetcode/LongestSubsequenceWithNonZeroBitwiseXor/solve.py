class Solution:
    def longestSubsequence(self, nums: List[int]) -> int:
        if all(val == 0 for val in nums):
            return 0
        
        x = 0
        for val in nums:
            x ^= val
        
        if x == 0:
            return len(nums) - 1
        return len(nums)