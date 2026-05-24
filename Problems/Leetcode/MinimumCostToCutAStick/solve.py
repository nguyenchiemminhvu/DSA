from typing import List, Tuple
import bisect

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        nc = len(cuts)
        cuts.sort()

        def find_range_indices(sorted: List[int], low: int, high: int) -> Tuple[int]:
            left = bisect.bisect_right(sorted, low)
            right = bisect.bisect_left(sorted, high)
            return (left, right)
        
        # min cost to do cut between l and r
        mem = {}
        def F(l: int, r: int) -> int:
            lc, rc = find_range_indices(cuts, l, r)
            if lc >= rc:
                return 0
            
            if (l, r) in mem:
                return mem[(l, r)]
            
            res = float('inf')
            for i in range(lc, rc):
                res = min(
                    res,
                    (r - l) + F(l, cuts[i]) + F(cuts[i], r)
                )
            
            mem[(l, r)] = res
            return res
        
        return F(0, n)