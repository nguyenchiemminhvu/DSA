from typing import List

class Solution:
    def minDeletion(self, nums: List[int]) -> int:
        n = len(nums)
        st = []
        for val in nums:
            if not st or len(st) % 2 == 0:
                st.append(val)
            else:
                if st[-1] != val:
                    st.append(val)
        if len(st) & 1:
            st.pop()
        return n - len(st)