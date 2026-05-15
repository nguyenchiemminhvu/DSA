from typing import List

class Solution:
    def mincostTickets(self, days: List[int], costs: List[int]) -> int:
        n = len(days)

        # mem = {}
        # def F(i: int, last_day: int) -> int:
        #     if i >= n:
        #         return 0
        #     if (i, last_day) in mem:
        #         return mem[(i, last_day)]
        #     res = float('inf')
        #     if days[i] < last_day:
        #         # this day is covered by previous ticket, just move on
        #         res = F(i + 1, last_day)
        #     else:
        #         cost_1 = F(i + 1, days[i] + 1)
        #         if cost_1 != float('inf'):
        #             res = min(res, costs[0] + cost_1)
        #         cost_7 = F(i + 1, days[i] + 7)
        #         if cost_7 != float('inf'):
        #             res = min(res, costs[1] + cost_7)
        #         cost_30 = F(i + 1, days[i] + 30)
        #         if cost_30 != float('inf'):
        #             res = min(res, costs[2] + cost_30)
        #     mem[(i, last_day)] = res
        #     return res
        # return F(0, 0)

        # s_days = set(days)
        # mem = {}
        # def F(i: int) -> int:
        #     if i <= 0:
        #         return 0
        #     if i in mem:
        #         return mem[i]
        #     res = float('inf')
        #     if i not in s_days:
        #         res = min(res, F(i - 1))
        #     else:
        #         res = min(res,
        #             min(
        #                 costs[0] + F(i - 1),
        #                 costs[1] + F(i - 7),
        #                 costs[2] + F(i - 30)
        #             )
        #         )
        #     mem[i] = res
        #     return res
        # return F(365)

        s_days = set(days)
        dp = [float('inf') for _ in range(366)]
        dp[0] = 0
        for i in range(366):
            if i not in s_days:
                dp[i] = min(dp[i], dp[i - 1] if i - 1 >= 0 else 0)
            else:
                dp[i] = min(dp[i], costs[0] + (dp[i - 1] if i - 1 >= 0 else 0))
                dp[i] = min(dp[i], costs[1] + (dp[i - 7] if i - 7 >= 0 else 0))
                dp[i] = min(dp[i], costs[2] + (dp[i - 30] if i - 30 >= 0 else 0))
        return dp[365]