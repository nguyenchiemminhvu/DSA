from typing import List

class Solution:
    def orderOfLargestPlusSign(self, n: int, mines: List[List[int]]) -> int:
        mine_set = set()
        for r, c in mines:
            mine_set.add((r, c))
        
        dp = [[n] * n for _ in range(n)]

        for r in range(n):
            count = 0
            for c in range(n):
                if (r, c) in mine_set:
                    count = 0
                else:
                    count += 1
                dp[r][c] = min(dp[r][c], count)
            
            count = 0
            for c in range(n - 1, -1, -1):
                if (r, c) in mine_set:
                    count = 0
                else:
                    count += 1
                dp[r][c] = min(dp[r][c], count)
        
        for c in range(n):
            count = 0
            for r in range(n):
                if (r, c) in mine_set:
                    count = 0
                else:
                    count += 1
                dp[r][c] = min(dp[r][c], count)
            
            count = 0
            for r in range(n - 1, -1, -1):
                if (r, c) in mine_set:
                    count = 0
                else:
                    count += 1
                dp[r][c] = min(dp[r][c], count)
        
        res = 0
        for row in dp:
            res = max(res, max(row))
        return res