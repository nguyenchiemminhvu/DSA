from typing import List

class Solution:
    def maxUncrossedLines(self, nums1: List[int], nums2: List[int]) -> int:
        n1, n2 = len(nums1), len(nums2)

        # mem = {}
        # def F(i1: int, i2: int) -> int:
        #     if i1 >= n1 or i2 >= n2:
        #         return 0
        #     if (i1, i2) in mem:
        #         return mem[(i1, i2)]
        #     res = 0
        #     if nums1[i1] == nums2[i2]:
        #         res = max(res, 1 + F(i1 + 1, i2 + 1))
        #     else:
        #         res = max(res, max(F(i1 + 1, i2), F(i1, i2 + 1)))
        #     mem[(i1, i2)] = res
        #     return res
        # return F(0, 0)

        dp = [[0 for _ in range(n2 + 1)] for _ in range(n1 + 1)]
        for i1 in range(n1 - 1, -1, -1):
            for i2 in range(n2 - 1, -1, -1):
                if nums1[i1] == nums2[i2]:
                    dp[i1][i2] = max(dp[i1][i2], 1 + dp[i1 + 1][i2 + 1])
                else:
                    dp[i1][i2] = max(dp[i1][i2], max(dp[i1 + 1][i2], dp[i1][i2 + 1]))
        return dp[0][0]