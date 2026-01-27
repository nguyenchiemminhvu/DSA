from typing import List
import heapq

class Solution:
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        n = len(heights)
        res = 0
        pq = []
        for i in range(1, n):
            diff = heights[i] - heights[i - 1]
            if diff > 0:
                bricks -= diff
                heapq.heappush(pq, -diff)
                if bricks < 0:
                    if ladders == 0:
                        break
                    ladders -= 1
                    bricks += -heapq.heappop(pq)
            res = i
        
        return res