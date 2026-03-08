from typing import List

class Solution:
    def minAbsoluteSumDiff(self, nums1: List[int], nums2: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(nums1)

        opts = sorted(nums1)

        def upper_bound(arr, target):
            left, right = 0, len(arr) - 1
            idx = len(arr)
            while left <= right:
                mid = (left + right) // 2
                if arr[mid] > target:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx

        reduced = 0
        total = 0

        for i in range(n):
            diff = abs(nums1[i] - nums2[i])
            total += diff

            upper = upper_bound(opts, nums2[i])

            best = diff

            if upper < n:
                best = min(best, abs(opts[upper] - nums2[i]))

            if upper > 0:
                best = min(best, abs(opts[upper - 1] - nums2[i]))

            reduced = max(reduced, diff - best)

        return (total - reduced) % MOD