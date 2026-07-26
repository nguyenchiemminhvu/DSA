from collections import defaultdict
import heapq
import math

class Solution:
    def minOperations(self, n: int, m: int) -> int:
        def get_primes(limit: int) -> set[int]:
            flags = [True] * limit
            flags[0] = flags[1] = False
            for i in range(2, int(math.sqrt(limit) + 1)):
                if flags[i]:
                    for p in range(i * i, limit, i):
                        flags[p] = False
            return set([i for i in range(2, limit) if flags[i]])
        
        primes = get_primes(10**4 + 1)
        
        if n in primes or m in primes:
            return -1
        
        if n == m:
            return n

        num_of_digits = 0
        temp = n
        while temp:
            num_of_digits += 1
            temp //= 10
        
        min_cost = defaultdict(lambda: int(0xFFFFFFFF))
        min_cost[n] = n
        pq = [(n, n)]
        while pq:
            cur_cost, cur_val = heapq.heappop(pq)
            if cur_cost > min_cost[cur_val]:
                continue
            if cur_val == m:
                break

            for i in range(num_of_digits):
                d = 10 ** i
                cands = []
                if (cur_val // d) % 10 < 9:
                    cands.append(cur_val + d)
                if (cur_val // d) % 10 > 0:
                    if i != num_of_digits - 1 or ((cur_val // d) % 10) > 1:
                        cands.append(cur_val - d)
                for adj_val in cands:
                    if adj_val < 0:
                        continue
                    if adj_val in primes:
                        continue
                    adj_cost = cur_cost + adj_val
                    if adj_cost < min_cost[adj_val]:
                        min_cost[adj_val] = adj_cost
                        heapq.heappush(pq, (adj_cost, adj_val))
        
        if min_cost[m] == 0xFFFFFFFF:
            return -1
        return min_cost[m]