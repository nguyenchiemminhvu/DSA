from typing import List

class Solution:
    def maxSumAfterPartitioning(self, arr: List[int], k: int) -> int:
        n = len(arr)

        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = 0
        #     for j in range(i, max(i - k, -1), -1):
        #         max_val = max(arr[j:i + 1])
        #         res = max(res, (max_val * (i - j + 1)) + F(j - 1))
        #     mem[i] = res
        #     return res
        # return F(n - 1)

        dp = [0] * n
        for i in range(n):
            max_val = arr[i]
            for j in range(i, max(i - k, -1), -1):
                max_val = max(max_val, arr[j])
                dp[i] = max(
                    dp[i],
                    max_val * (i - j + 1) + (dp[j - 1] if j - 1 >= 0 else 0)
                )
        return dp[n - 1]