from typing import List
import heapq

class Solution:
    def stoneGameVI(self, a: List[int], b: List[int]) -> int:
        n = len(a)
        pq = []
        for i in range(n):
            heapq.heappush(pq, (-(a[i] + b[i]), (a[i], b[i])))
        
        turn = 0
        table = [0, 0]
        while pq:
            _, vals = heapq.heappop(pq)
            table[turn] += vals[turn]
            turn = (turn + 1) % 2
        
        if table[0] == table[1]:
            return 0
        return 1 if table[0] > table[1] else -1