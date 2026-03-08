from typing import List

class Solution:
    def findBestValue(self, arr: List[int], target: int) -> int:
        left = 0
        right = max(arr)

        def f_sum_threshold(threshold: int) -> int:
            return sum(min(val, threshold) for val in arr)

        best_val = 0
        best_diff = float('inf')
        while left <= right:
            mid1 = left + (right - left) // 3
            mid2 = right - (right - left) // 3

            s1 = f_sum_threshold(mid1)
            s2 = f_sum_threshold(mid2)
            diff1 = abs(s1 - target)
            diff2 = abs(s2 - target)

            if diff1 < best_diff or (diff1 == best_diff and mid1 < best_val):
                best_diff = diff1
                best_val = mid1
            if diff2 < best_diff or (diff2 == best_diff and mid2 < best_val):
                best_diff = diff2
                best_val = mid2

            if diff1 > diff2:
                left = mid1 + 1
            else:
                right = mid2 - 1

        return best_val