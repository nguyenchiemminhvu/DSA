from typing import List

class Solution:
    def bowlSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        left = [-1] * n
        right = [n] * n

        st = []
        for i in range(n):
            while st and nums[st[-1]] <= nums[i]:
                st.pop()
            if st:
                left[i] = st[-1]
            st.append(i)
        
        st = []
        for i in range(n - 1, -1, -1):
            while st and nums[st[-1]] <= nums[i]:
                st.pop()
            if st:
                right[i] = st[-1]
            st.append(i)
        
        s = set()
        for i in range(1, n - 1):
            l, r = left[i], right[i]
            if l >= 0 and r < n:
                s.add((l, r))
        return len(s)