class Solution:
    def minCuttingCost(self, n: int, m: int, k: int) -> int:
        arr = sorted([m, n], reverse=True)
        cost = 0
        for val in arr:
            if val <= k:
                break
            cost += (val - k) * k
        return cost