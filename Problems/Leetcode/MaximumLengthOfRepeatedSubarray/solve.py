from typing import List

class Solution:
    def findLength(self, nums1: List[int], nums2: List[int]) -> int:
        n1, n2 = len(nums1), len(nums2)

        # mem = {}
        # def F(i1: int, i2: int):
        #     if i1 < 0 or i2 < 0:
        #         return 0
        #     if (i1, i2) in mem:
        #         return mem[(i1, i2)]
        #     res = 0
        #     if nums1[i1] == nums2[i2]:
        #         res = max(res, 1 + F(i1 - 1, i2 - 1))
        #     else:
        #         res = 0
        #     mem[(i1, i2)] = res
        #     return res
        # res = 0
        # for i in range(n1):
        #     for j in range(n2):
        #         res = max(res, F(i, j))
        # return res

        dp = [[0] * n2 for _ in range(n1)]
        for i in range(n1):
            for j in range(n2):
                if nums1[i] == nums2[j]:
                    dp[i][j] = max(dp[i][j], 1 + (dp[i - 1][j - 1] if i - 1 >= 0 and j - 1 >= 0 else 0))
                else:
                    dp[i][j] = 0
        return max(max(row) for row in dp)