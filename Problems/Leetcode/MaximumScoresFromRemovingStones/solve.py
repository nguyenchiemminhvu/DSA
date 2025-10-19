import heapq

class Solution:
    def maximumScore(self, a: int, b: int, c: int) -> int:
        pq = [-a, -b, -c]
        heapq.heapify(pq)

        res = 0
        while len(pq) > 1:
            first = heapq.heappop(pq)
            second = heapq.heappop(pq)
            first *= -1
            second *= -1
            res += 1
            first -= 1
            second -= 1
            if first > 0:
                heapq.heappush(pq, -first)
            if second > 0:
                heapq.heappush(pq, -second)
        return res