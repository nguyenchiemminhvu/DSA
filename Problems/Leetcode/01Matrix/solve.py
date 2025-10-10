from collections import deque
from typing import List

class Solution:
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        INF = 0x7FFFFFFF
        m, n = len(mat), len(mat[0])
        dp = [[0 if mat[i][j] == 0 else INF for j in range(n)] for i in range(m)]
        Q = deque([(i, j) for i in range(m) for j in range(n) if mat[i][j] == 0])
        steps = 0
        while len(Q) > 0:
            cur_len = len(Q)
            while cur_len:
                r, c = Q.popleft()
                cur_len -= 1

                neighbors = [(r + 1, c), (r - 1, c), (r, c + 1), (r, c - 1)]
                for neighbor in neighbors:
                    next_r, next_c = neighbor
                    if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n:
                        if mat[next_r][next_c] != 0 and dp[next_r][next_c] >= steps + 1:
                            dp[next_r][next_c] = steps + 1
                            Q.append((next_r, next_c))
            steps += 1
        return dp