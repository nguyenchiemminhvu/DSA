import heapq

class Solution:
    def repeatLimitedString(self, s: str, repeatLimit: int) -> str:
        freq = {}
        for c in s:
            freq[c] = freq.get(c, 0) + 1
        
        pq = []
        for c, f in freq.items():
            heapq.heappush(pq, (-ord(c), f))
        
        res = ""
        while pq:
            c, f = heapq.heappop(pq)
            c *= -1
            if len(res) > 0 and chr(c) == res[-1]:
                if pq:
                    cc, ff = heapq.heappop(pq)
                    cc *= -1
                    res += chr(cc)
                    ff -= 1
                    if ff > 0:
                        heapq.heappush(pq, (-cc, ff))
                else:
                    break
            else:
                n = min(f, repeatLimit)
                res += chr(c) * n
                f -= n

            if f > 0:
                heapq.heappush(pq, (-c, f))

        return res