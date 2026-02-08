from typing import List
import heapq

class Solution:
    def eatenApples(self, apples: List[int], days: List[int]) -> int:
        n = len(apples)
        pq = [] # (rot_after_day, num_apple)
        res = 0
        for i in range(n):
            if apples[i] > 0 and days[i] > 0:
                heapq.heappush(pq, (i + days[i], apples[i]))
            
            while pq and pq[0][0] <= i:
                heapq.heappop(pq)
            
            if pq:
                rot_day, apple = heapq.heappop(pq)
                apple -= 1
                res += 1
                if apple > 0:
                    heapq.heappush(pq, (rot_day, apple))
        
        cur_day = n - 1
        while pq:
            cur_day += 1
            while pq and pq[0][0] <= cur_day:
                heapq.heappop(pq)
            if pq:
                rot_day, apple = heapq.heappop(pq)
                apple -= 1
                res += 1
                if apple > 0:
                    heapq.heappush(pq, (rot_day, apple))
        
        return res