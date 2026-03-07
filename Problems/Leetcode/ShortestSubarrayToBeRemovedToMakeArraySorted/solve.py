from typing import List

class Solution:
    def findLengthOfShortestSubarray(self, arr: List[int]) -> int:
        n = len(arr)
        left = 1
        while left < n and arr[left] >= arr[left - 1]:
            left += 1
        
        if left >= n:
            return 0
        
        right = n - 2
        while right >= 0 and arr[right] <= arr[right + 1]:
            right -= 1
        
        left -= 1
        right += 1
        res = min(n - left - 1, right)

        i = 0
        j = right
        while i <= left and j < n:
            if arr[i] <= arr[j]:
                res = min(res, j - i - 1)
                i += 1
            else:
                j += 1
        return res