from typing import List

class Solution:
    def minCost(self, colors: str, neededTime: List[int]) -> int:
        n = len(colors)
        i = 0
        res = 0
        while i < n:
            cur_max = neededTime[i]
            cur_sum = neededTime[i]
            j = i + 1
            if j < n and colors[j] == colors[i]:
                while j < n and colors[j] == colors[i]:
                    cur_max = max(cur_max, neededTime[j])
                    cur_sum += neededTime[j]
                    j += 1
                res += (cur_sum - cur_max)
            i = j
        return res