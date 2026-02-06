from typing import List
import heapq

class Solution:
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
        n1, n2 = len(nums1), len(nums2)
        i1 = i2 = 0
        smallest_pairs = []
        pq = [(nums1[i1] + nums2[i2], (i1, i2))] # [(sum_pair, (u, v))]
        visited = set()
        visited.add((i1, i2))
        while pq and len(smallest_pairs) < k:
            sum_pair, (i1, i2) = heapq.heappop(pq)
            smallest_pairs.append([i1, i2])

            for j1, j2 in [(i1 + 1, i2), (i1, i2 + 1)]:
                if j1 < n1 and j2 < n2 and (j1, j2) not in visited:
                    visited.add((j1, j2))
                    heapq.heappush(pq, (nums1[j1] + nums2[j2], (j1, j2)))
        
        return [[nums1[i], nums2[j]] for i, j in smallest_pairs[:k]]