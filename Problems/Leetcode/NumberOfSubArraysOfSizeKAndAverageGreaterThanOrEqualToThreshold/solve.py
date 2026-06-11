from typing import List

class Solution:
    def numOfSubarrays(self, arr: List[int], k: int, threshold: int) -> int:
        n = len(arr)
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + arr[i]

        count = 0
        for i in range(n - k + 1):
            s = prefix_sum[i + k] - prefix_sum[i]
            avg = float(s / k)
            if avg >= threshold:
                count += 1

        return count