from typing import List

class Solution:
    def taskSchedulerII(self, tasks: List[int], space: int) -> int:
        prev_day = {}
        cur_day = 1
        for task in tasks:
            prev = float('-inf')
            if task in prev_day:
                prev = prev_day[task]
            if cur_day <= prev + space:
                cur_day = prev + space + 1
            
            prev_day[task] = cur_day
            cur_day += 1
        return cur_day - 1