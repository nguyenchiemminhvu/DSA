from typing import List

class Solution:
    def shortestToChar(self, s: str, c: str) -> List[int]:
        def lower_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left, right, found = 0, n - 1, n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] >= target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found

        arr = []
        for i in range(len(s)):
            if s[i] == c:
                arr.append(i)
        
        res = []
        for i in range(len(s)):
            found = lower_bound(arr, i)
            if found == len(arr):
                res.append(abs(i - arr[found - 1]))
            elif found == 0:
                res.append(abs(i - arr[found]))
            else:
                res.append(min(abs(i - arr[found]), abs(i - arr[found - 1])))
        return res