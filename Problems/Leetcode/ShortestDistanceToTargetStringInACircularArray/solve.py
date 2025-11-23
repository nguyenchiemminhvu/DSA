from typing import List

class Solution:
    def closestTarget(self, words: List[str], target: str, startIndex: int) -> int:
        def upper_bound(arr: List[int], target: int) -> int:
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
        
        found = []
        for i, word in enumerate(words):
            if word == target:
                found.append(i)
        
        if not found:
            return -1
        
        upper = upper_bound(found, startIndex)
        if upper == len(found):
            return min(startIndex - found[-1], len(words) - startIndex + found[0])
        elif upper == 0:
            return min(found[0] - startIndex, startIndex + len(words) - found[-1])
        else:
            return min(found[upper] - startIndex, startIndex - found[upper - 1])