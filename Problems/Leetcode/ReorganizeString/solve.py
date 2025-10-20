import heapq

class Solution:
    def reorganizeString(self, s: str) -> str:
        freq = {}
        for c in s:
            freq[c] = freq.get(c, 0) + 1
        pq = []
        for k, v in freq.items():
            heapq.heappush(pq, (-v, k))
        
        s = ""
        while pq:
            f, c = heapq.heappop(pq)
            f *= -1
            if s and s[-1] == c:
                if pq:
                    ff, cc = heapq.heappop(pq)
                    ff *= -1
                    s += cc
                    ff -= 1
                    if ff > 0:
                        heapq.heappush(pq, (-ff, cc))
                else:
                    return ""
            else:
                s += c
                f -= 1

            if f > 0:
                heapq.heappush(pq, (-f, c))

        return s