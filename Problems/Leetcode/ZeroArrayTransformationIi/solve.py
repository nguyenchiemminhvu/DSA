from typing import List

class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)
        m = len(queries)

        def check_possible(k: int) -> bool:
            temp = [0] * (n + 1)
            for i in range(k):
                l, r, val = queries[i]
                temp[l] += val
                temp[r+1] -= val
            for i in range(1, n + 1):
                temp[i] += temp[i - 1]
            return all(temp[i] >= nums[i] for i in range(n))

        left = 0
        right = m
        k = float('inf')
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                k = mid
                right = mid - 1
            else:
                left = mid + 1
        return -1 if k == float('inf') else k