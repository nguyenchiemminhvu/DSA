from typing import List

class Solution:
    def edgeScore(self, edges: List[int]) -> int:
        n = len(edges)
        in_score = [0] * n
        for i in range(n):
            adj = edges[i]
            in_score[adj] += i
        
        max_score = max(in_score)
        for i in range(n):
            if in_score[i] == max_score:
                return i
        return -1