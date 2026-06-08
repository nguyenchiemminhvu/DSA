from typing import List
import heapq

class Solution:
    def isPossible(self, target: List[int]) -> bool:
        n = len(target)
        if n == 1:
            return target[0] == 1

        pq = []
        s = 0
        for val in target:
            s += val
            heapq.heappush(pq, -val)
                
        while pq and -pq[0] > 1:
            largest = -heapq.heappop(pq)
            rest = s - largest

            if rest == 1:
                return True
            
            if rest < 1 or largest <= rest:
                return False
            
            next_val = largest % rest
            if next_val == 0:
                next_val = rest
            
            s = rest + next_val
            heapq.heappush(pq, -next_val)

        return True