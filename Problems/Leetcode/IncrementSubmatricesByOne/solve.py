from typing import List

class Solution:
    def rangeAddQueries(self, n: int, queries: List[List[int]]) -> List[List[int]]:
        prefix = [[0] * n for _ in range(n)]
        for a, b, c, d in queries:
            for r in range(a, c + 1):
                prefix[r][b] += 1
                if d + 1 < n:
                    prefix[r][d + 1] -= 1
        
        for i in range(n):
            for j in range(1, n):
                prefix[i][j] += prefix[i][j - 1]
        
        return prefix