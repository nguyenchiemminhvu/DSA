from typing import List

class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        n = len(arr)
        left = 1
        right = n - 2

        while left <= right:
            mid = left + (right - left) // 2
            if arr[mid] > arr[mid - 1] and arr[mid] > arr[mid + 1]:
                return mid
            if arr[mid] > arr[mid - 1] and arr[mid] < arr[mid + 1]:
                left = mid + 1
            else:
                right = mid - 1
        return -1