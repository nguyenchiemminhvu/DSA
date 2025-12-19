from typing import List
from itertools import permutations

class Solution:
    def nextBeautifulNumber(self, n: int) -> int:
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

        base = ['1', '22', '122', '333', '1333', '4444', '22333', '14444', '55555', '155555', '224444', '122333', '666666', '1224444', '1666666', '7777777']
        arr = []
        for s in base:
            arr.extend(list(permutations(s)))
        for i in range(len(arr)):
            sub = arr[i]
            val = 0
            for c in sub:
                val = val * 10 + int(c)
            arr[i] = val
        arr = sorted(set(arr))
        upper = upper_bound(arr, n)
        return arr[upper]
