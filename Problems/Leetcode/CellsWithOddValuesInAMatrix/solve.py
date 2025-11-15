from typing import List

class Solution:
    def oddCells(self, m: int, n: int, indices: List[List[int]]) -> int:
        rows = [0] * m
        cols = [0] * n
        for r, c in indices:
            rows[r] += 1
            cols[c] += 1
        
        count = 0
        for i in range(m):
            for j in range(n):
                count += (rows[i] + cols[j]) & 1
        return count