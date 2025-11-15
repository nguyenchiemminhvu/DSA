from typing import List

class Solution:
    def countNegatives(self, grid: List[List[int]]) -> int:
        def upper_bound_reverse(arr: List[int], target) -> int:
            n = len(arr)
            left, right, found = 0, n - 1, n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] < target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found
        
        res = 0
        for row in grid:
            idx = upper_bound_reverse(row, 0)
            res += len(row) - idx
        return res