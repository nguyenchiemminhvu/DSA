from typing import List

class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        m = len(strs)
        n = len(strs[0])
        dp = [1] * n
        for col in range(1, n):
            for prev in range(0, col):
                all_valid = True
                for row in range(m):
                    if strs[row][col] < strs[row][prev]:
                        all_valid = False
                        break
                if all_valid:
                    dp[col] = max(dp[col], dp[prev] + 1)
        return n - max(dp)