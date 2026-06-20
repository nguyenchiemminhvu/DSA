from typing import List
import heapq

class Solution:
    def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
        n = len(profits)
        projects = sorted(zip(capital, profits))

        pq = []
        ip = 0
        for _ in range(k):
            while ip < n and projects[ip][0] <= w:
                heapq.heappush(pq, -projects[ip][1])
                ip += 1
            
            if not pq:
                break
            
            best_profit = -heapq.heappop(pq)
            w += best_profit
        
        return w