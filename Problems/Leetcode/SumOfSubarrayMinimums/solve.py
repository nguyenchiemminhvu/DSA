from typing import List

class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        mod = 10**9 + 7
        n = len(arr)
        left = [-1] * n
        right = [n] * n

        # left to right - find smaller index to the left side
        st = []
        for i in range(n):
            while st and arr[st[-1]] >= arr[i]:
                st.pop()
            if st:
                left[i] = st[-1]
            st.append(i)

        # right to left - find smaller index to the right side
        st = []
        for i in range(n - 1, -1, -1):
            while st and arr[st[-1]] > arr[i]:
                st.pop()
            if st:
                right[i] = st[-1]
            st.append(i)

        res = 0
        for i in range(n):
            # The number of subarrays where arr[i] is the minimum is (i - left[i]) × (right[i] - i).
            res = ((res % mod) + arr[i] * ((i - left[i]) * (right[i] - i)) % mod) % mod

        return res