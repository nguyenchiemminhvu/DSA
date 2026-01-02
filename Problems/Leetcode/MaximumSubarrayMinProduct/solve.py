from typing import List

class Solution:
    def maxSumMinProduct(self, nums: List[int]) -> int:
        mod = 10**9 + 7
        n = len(nums)
        
        prefix_sum = [0] + nums[:]
        for i in range(1, len(prefix_sum)):
            prefix_sum[i] += prefix_sum[i - 1]
        
        min_left = [-1] * n
        min_right = [n] * n
        
        st = []
        for i in range(n):
            while st and nums[st[-1]] >= nums[i]:
                st.pop()
            if st:
                min_left[i] = st[-1]
            st.append(i)
        
        st = []
        for i in range(n - 1, -1, -1):
            while st and nums[st[-1]] > nums[i]:
                st.pop()
            if st:
                min_right[i] = st[-1]
            st.append(i)
        
        res = 0
        for i in range(n):
            left = min_left[i] + 1
            right = min_right[i] - 1
            cur_sum = prefix_sum[right + 1] - prefix_sum[left]
            res = max(res, nums[i] * cur_sum)
        return res % mod