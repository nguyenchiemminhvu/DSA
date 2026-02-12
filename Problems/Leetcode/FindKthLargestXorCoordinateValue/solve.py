from typing import List
import heapq

class Solution:
    def kthLargestValue(self, mat: List[List[int]], k: int) -> int:
        m = len(mat)
        n = len(mat[0])

        pq = []
        for i in range(m):
            cur = 0
            for j in range(n):
                cur ^= mat[i][j]
                temp = cur
                if i > 0:
                    temp ^= mat[i - 1][j]
                heapq.heappush(pq, temp)
                if len(pq) > k:
                    heapq.heappop(pq)
                mat[i][j] = temp
        return pq[0]