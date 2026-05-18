from typing import List

class Solution:
    def maxJumps(self, arr: List[int], d: int) -> int:
        n = len(arr)

        # mem = {}
        # def F(i: int) -> int:
        #     if i < 0 or i >= n:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = 1
        #     cur_max = arr[i]
        #     l_bound = i - d
        #     r_bound = i + d
        #     for j in range(i - 1, l_bound - 1, -1):
        #         if j < 0 or arr[j] >= cur_max:
        #             break
        #         res = max(res, 1 + F(j))
        #     for j in range(i + 1, r_bound + 1):
        #         if j >= n or arr[j] >= cur_max:
        #             break
        #         res = max(res, 1 + F(j))
        #     mem[i] = res
        #     return res
        # res = 1
        # for i in range(n):
        #     res = max(res, F(i))
        # return res

        dp = [1] * n
        sorted_idx = [i for i in range(n)]
        sorted_idx.sort(key=lambda x: arr[x])
        for i in range(len(sorted_idx)):
            idx = sorted_idx[i]
            cur_max = arr[idx]
            l_bound = idx - d
            r_bound = idx + d
            for j in range(idx - 1, l_bound - 1, -1):
                if j < 0 or arr[j] >= cur_max:
                    break
                dp[idx] = max(dp[idx], 1 + dp[j])
            for j in range(idx + 1, r_bound + 1):
                if j >= n or arr[j] >= cur_max:
                    break
                dp[idx] = max(dp[idx], 1 + dp[j])
        return max(dp)