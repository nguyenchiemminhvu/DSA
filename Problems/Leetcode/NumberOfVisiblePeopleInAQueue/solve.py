from typing import List

class Solution:
    def canSeePersonsCount(self, heights: List[int]) -> List[int]:
        n = len(heights)

        res = [0] * n
        st = []
        for i in range(n - 1, -1, -1):
            while st and heights[st[-1]] <= heights[i]:
                res[i] += 1
                st.pop()
            if st:
                res[i] += 1
            st.append(i)
        
        return res