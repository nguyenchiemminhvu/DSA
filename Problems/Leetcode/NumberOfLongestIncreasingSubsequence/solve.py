from typing import List, Tuple

class Solution:
    def findNumberOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        
        # F(i) -> tuple(LIS from 0...i, number of LIS from 0...i)
        # mem = {}
        # def F(i: int) -> Tuple[int]:
        #     if i in mem:
        #         return mem[i]
        #     max_len = 1
        #     max_count = 1

        #     for j in range(i):
        #         if nums[i] > nums[j]:
        #             prev_len, prev_count = F(j)
        #             if prev_len + 1 > max_len:
        #                 max_len = prev_len + 1
        #                 max_count = prev_count
        #             elif prev_len + 1 == max_len:
        #                 max_count += prev_count
        #     mem[i] = (max_len, max_count)
        #     return mem[i]

        # global_max_len = 0
        # res = 0
        # for i in range(n):
        #     max_len, count = F(i)
        #     if global_max_len < max_len:
        #         global_max_len = max_len
        #         res = count
        #     elif global_max_len == max_len:
        #         res += count
        # return res

        dp = [(1, 1)] * n
        for i in range(n):
            max_len, max_count = 1, 1
            for j in range(i):
                if nums[i] > nums[j]:
                    prev_len, prev_count = dp[j]
                    if prev_len + 1 > max_len:
                        max_len = prev_len + 1
                        max_count = prev_count
                    elif prev_len + 1 == max_len:
                        max_count += prev_count
            dp[i] = (max_len, max_count)
        
        global_max_len = 0
        res = 0
        for i in range(n):
            l, c = dp[i]
            if global_max_len < l:
                global_max_len = l
                res = c
            elif global_max_len == l:
                res += c
        return res