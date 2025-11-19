from typing import List

class Solution:
    def construct2DArray(self, original: List[int], m: int, n: int) -> List[List[int]]:
        no = len(original)
        if no % m != 0 or no % n != 0 or m * n != no:
            return []
        grid = [[0] * n for _ in range(m)]
        for i in range(no):
            r = i // n
            c = i % n
            grid[r][c] = original[i]
        return grid