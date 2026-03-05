from typing import List

class Solution:
    def numFriendRequests(self, ages: List[int]) -> int:
        ages.sort()
        n = len(ages)
        
        def upper_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left = 0
            right = n - 1
            idx = n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx

        res = 0
        for i in range(0, n):
            age = ages[i]
            if age < 15:
                continue
            
            left = int(age * 0.5 + 7)
            right = age
            upper_left = upper_bound(ages, left)
            upper_right = upper_bound(ages, right)
            res += max(0, (upper_right - upper_left) - 1) # minus 1 of x-self

        return res