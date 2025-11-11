from collections import Counter
import heapq

class Solution:
    def minDeletion(self, s: str, k: int) -> int:
        f = Counter(s)
        pq = [(v, k) for k, v in f.items()]
        heapq.heapify(pq)

        res = 0
        while len(pq) > k:
            freq, val = heapq.heappop(pq)
            res += freq

        return res