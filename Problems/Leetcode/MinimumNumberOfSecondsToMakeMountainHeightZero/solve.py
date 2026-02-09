from typing import List
import heapq

class Solution:
    def minNumberOfSeconds(self, height: int, times: List[int]) -> int:
        n = len(times)
        pq = [(t, t, 1) for t in times] # (cur_time_cost, init_time, multipler)
        heapq.heapify(pq)

        total_time_cost = 0
        while height > 0:
            cur_time_cost, init_time, multiplier = heapq.heappop(pq)
            total_time_cost = max(total_time_cost, cur_time_cost)
            multiplier += 1
            cur_time_cost += init_time * multiplier
            heapq.heappush(pq, (cur_time_cost, init_time, multiplier))
            height -= 1
        
        return total_time_cost