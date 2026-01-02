from typing import List

class Solution:
    def maxWidthRamp(self, nums: List[int]) -> int:
        n = len(nums)

        st = []
        for i in range(n):
            if not st or nums[st[-1]] > nums[i]:
                st.append(i)
        
        max_ramp = 0
        for i in range(n - 1, -1, -1):
            while st and nums[st[-1]] <= nums[i]:
                max_ramp = max(max_ramp, i - st[-1])
                st.pop()
        return max_ramp