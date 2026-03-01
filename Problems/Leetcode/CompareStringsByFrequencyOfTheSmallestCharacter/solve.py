from typing import List

class Solution:
    def numSmallerByFrequency(self, queries: List[str], words: List[str]) -> List[int]:
        def lower_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left, right = 0, n - 1
            idx = -1
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] <= target:
                    idx = mid
                    left = mid + 1
                else:
                    right = mid - 1
            return idx
        
        arr = []
        for word in words:
            f = word.count(min(word))
            arr.append(f)
        arr.sort()

        res = []
        for query in queries:
            f = query.count(min(query))
            lower = lower_bound(arr, f)
            res.append(len(arr) - lower - 1)
        return res