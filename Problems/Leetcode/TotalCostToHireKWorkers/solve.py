import heapq
from typing import List

class Solution:
    def totalCost(self, costs: List[int], k: int, candidates: int) -> int:
        n = len(costs)
        l = 0
        r = n - 1
        pq = []

        if candidates * 2 >= n:
            l = n
            r = -1
            for i in range(n):
                heapq.heappush(pq, (costs[i], i))
        else:
            for _ in range(candidates):
                heapq.heappush(pq, (costs[l], l))
                l += 1
            for _ in range(candidates):
                heapq.heappush(pq, (costs[r], r))
                r -= 1

        chosen = [False] * n
        res = 0

        while k > 0:
            while chosen[pq[0][1]]:
                heapq.heappop(pq)

            cost, idx = heapq.heappop(pq)
            res += cost
            chosen[idx] = True
            k -= 1

            if l <= r:
                if idx < l:
                    heapq.heappush(pq, (costs[l], l))
                    l += 1
                else:
                    heapq.heappush(pq, (costs[r], r))
                    r -= 1

        return res