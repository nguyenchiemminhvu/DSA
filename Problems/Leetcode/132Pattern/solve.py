from typing import List

class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        n = len(nums)
        left_min = [float('inf')] * n
        cur_min = float('inf')
        left_gt = [-1] * n
        st = []
        for i, val in enumerate(nums):
            if val < cur_min:
                cur_min = val
            left_min[i] = cur_min

            while st and nums[st[-1]] <= val:
                st.pop()
            if st:
                left_gt[i] = st[-1]
            st.append(i)

        for i in range(2, n):
            if left_gt[i] != -1:
                pivot_3 = left_gt[i]
                if pivot_3 > 0 and left_min[pivot_3 - 1] < nums[i]:
                    return True
        return False