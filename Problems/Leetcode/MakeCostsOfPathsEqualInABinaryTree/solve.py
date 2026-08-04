from typing import List

class Solution:
    def minIncrements(self, n: int, cost: List[int]) -> int:
        res = 0
        def dfs(root):
            nonlocal res
            if root > n:
                return 0
            
            left = dfs(root * 2)
            right = dfs(root * 2 + 1)
            diff = abs(right - left)
            res += diff
            return cost[root - 1] + max(left, right)

        dfs(1)
        return res