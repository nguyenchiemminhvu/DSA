import heapq

class Solution:
    def getKth(self, lo: int, hi: int, k: int) -> int:
        mem = {}
        def power_value(val: int) -> int:
            if val == 1:
                return 0
            if val in mem:
                return mem[val]
            res = 0
            if val & 1:
                res += 1 + power_value(val * 3 + 1)
            else:
                res += 1 + power_value(val // 2)
            mem[val] = res
            return res

        pq = []
        for val in range(lo, hi + 1):
            p = power_value(val)
            heapq.heappush(pq, (-p, -val))
            if len(pq) > k:
                heapq.heappop(pq)
        return -pq[0][1]