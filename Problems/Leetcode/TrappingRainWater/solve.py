from typing import List

class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)

        left_greater = [-1] * n
        right_greater = [n] * n

        st = []
        for i in range(n):
            while st and height[st[-1]] < height[i]:
                right_greater[st[-1]] = i
                st.pop()
            if st:
                left_greater[i] = st[-1]
            st.append(i)
        
        left_max_idx = 0
        for i in range(1, n):
            if left_greater[i] != -1 and height[left_max_idx] > height[left_greater[i]]:
                left_greater[i] = left_max_idx
            if height[left_max_idx] < height[i]:
                left_max_idx = i
        
        right_max_idx = n - 1
        for i in range(n - 2, -1, -1):
            if right_greater[i] != n and height[right_max_idx] > height[right_greater[i]]:
                right_greater[i] = right_max_idx
            if height[right_max_idx] < height[i]:
                right_max_idx = i
        
        res = 0
        for i in range(n):
            left = left_greater[i]
            right = right_greater[i]
            if left != -1 and right != n:
                res += min(height[left], height[right]) - height[i]
        return res