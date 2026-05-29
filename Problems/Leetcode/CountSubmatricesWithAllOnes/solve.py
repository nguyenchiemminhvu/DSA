from typing import List

class Solution:
    def numSubmat(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        # res = 0
        # dp = [0] * n
        # for row in grid:
        #     for i in range(n):
        #         if row[i] == 0:
        #             dp[i] = 0
        #         else:
        #             dp[i] += 1
        #     for i in range(n):
        #         for j in range(i, n):
        #             mi = min(dp[i:j + 1])
        #             res += mi
        # return res

        res = 0
        height = [0] * n
        for row in grid:
            for i in range(n):
                if row[i] == 0:
                    height[i] = 0
                else:
                    height[i] += 1
            
            st = [] # monotonic stack to find index of smaller height on the left and right
            left = [-1] * n
            right = [n] * n
            for i, h in enumerate(height):
                while st and height[st[-1]] >= h:
                    right[st[-1]] = i
                    st.pop()
                if st:
                    left[i] = st[-1]
                st.append(i)

            for i in range(n):
                res += height[i] * (i - left[i]) * (right[i] - i)
        return res