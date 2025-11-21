from typing import List

class Solution:
    def findTheDistanceValue(self, arr1: List[int], arr2: List[int], d: int) -> int:
        def upper_bound(arr:List[int], target:int) -> int:
            n = len(arr)
            left, right, found = 0, n - 1, n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found
        
        n1, n2 = len(arr1), len(arr2)
        arr2.sort()
        count = 0
        for val in arr1:
            idx = upper_bound(arr2, val)
            check = True
            if idx < n2 and arr2[idx] - val <= d:
                check = False
            if idx - 1 >= 0 and val - arr2[idx - 1] <= d:
                check = False
            count += int(check)
        return count