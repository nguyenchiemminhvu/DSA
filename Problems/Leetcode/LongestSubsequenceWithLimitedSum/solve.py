from typing import List

class Solution:
    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        def upper_bound(arr: List[int], target) -> int:
            left = 0
            right = len(arr) - 1
            found = right + 1
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found

        nums.sort()
        for i in range(1, len(nums)):
            nums[i] += nums[i - 1]

        res = []
        for query in queries:
            res.append(upper_bound(nums, query))
        return res