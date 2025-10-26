import heapq

class Solution:
    def strWithout3a3b(self, a: int, b: int) -> str:
        pq = [(-a, 'a'), (-b, 'b')]
        heapq.heapify(pq)
        res = ""
        while pq:
            f, c = heapq.heappop(pq)
            f *= -1
            if len(res) > 0 and c == res[-1]:
                if pq:
                    ff, cc = heapq.heappop(pq)
                    ff *= -1
                    res += cc
                    ff -= 1
                    if ff > 0:
                        heapq.heappush(pq, (-ff, cc))
                else:
                    break
            else:
                n = min(f, 2)
                res += c * n
                f -= n

            if f > 0:
                heapq.heappush(pq, (-f, c))

        return res