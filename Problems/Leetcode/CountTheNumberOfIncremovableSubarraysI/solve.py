from typing import List

class Solution:
    def incremovableSubarrayCount(self, arr: List[int]) -> int:
        def is_sorted(arr: List[int]) -> bool:
            for i in range(1, len(arr)):
                if arr[i] <= arr[i - 1]:
                    return False
            return True
        
        n = len(arr)
        count = 0
        for i in range(n):
            for j in range(i, n):
                sub = arr[0:i] + arr[j+1:]
                if is_sorted(sub):
                    count += 1
        return count