from typing import List

class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        nums.extend(nums[:])
        nn = len(nums)
        next_gt = [-1] * nn
        st = []
        for i in range(nn - 1, -1, -1):
            val = nums[i]
            while st and nums[st[-1]] <= val:
                st.pop()
            
            if st:
                next_gt[i] = nums[st[-1]]
            
            st.append(i)

        return next_gt[0:nn // 2]