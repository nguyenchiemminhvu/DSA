from collections import Counter
import heapq

class Solution:
    def frequencySort(self, s: str) -> str:
        f = Counter(s)
        
        pq = []
        for k, v in f.items():
            heapq.heappush(pq, (-v, k))
        
        res = ""
        while pq:
            count, ch = heapq.heappop(pq)
            count *= -1
            res += ch * count
        return res