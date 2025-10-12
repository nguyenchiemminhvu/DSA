from typing import List

class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        n = len(heights)
        s_left = [-1] * n
        s_right = [n] * n

        # Find nearest smaller element to the left using monotonic stack
        st = []
        for i in range(n):
            while st and heights[i] <= heights[st[-1]]:
                st.pop()
            if st:
                s_left[i] = st[-1]
            st.append(i)

        # Find nearest smaller element to the right using monotonic stack
        st = []
        for i in range(n - 1, -1, -1):
            while st and heights[i] <= heights[st[-1]]:
                st.pop()
            if st:
                s_right[i] = st[-1]
            st.append(i)
        
        res = 0
        for i in range(n):
            res = max(res, heights[i] * (s_right[i] - s_left[i] - 1))

        return max(res, min(heights) * n)