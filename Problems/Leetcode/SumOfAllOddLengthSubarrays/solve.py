from typing import List

class Solution:
    def sumOddLengthSubarrays(self, arr: List[int]) -> int:
        n = len(arr)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + arr[i]

        res = 0
        for sublen in range(0, n, 2):
            left = 0
            right = left + sublen
            while right < n:
                res += (prefix[right + 1] - prefix[left])
                left += 1
                right += 1
        return res