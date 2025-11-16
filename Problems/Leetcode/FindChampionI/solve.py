from typing import List

class Solution:
    def findChampion(self, grid: List[List[int]]) -> int:
        n = len(grid)
        max_sum = 0
        max_team = -1
        for i, row in enumerate(grid):
            cur_sum = sum(row)
            if max_sum < cur_sum:
                max_sum = cur_sum
                max_team = i
        return max_team