from typing import List

class Solution:
    def maximumPossibleSize(self, nums: List[int]) -> int:
        n = len(nums)

        right_gt = [n] * n
        st = []
        for i in range(n - 1, -1, -1):
            while st and nums[st[-1]] < nums[i]:
                st.pop()
            if st:
                right_gt[i] = st[-1]
            st.append(i)

        i = 0
        remain = n
        while i < n:
            right = right_gt[i]
            remain -= (right - i - 1)
            i = right

        return remain