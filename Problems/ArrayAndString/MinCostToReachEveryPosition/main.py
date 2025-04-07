# https://leetcode.com/problems/minimum-cost-to-reach-every-position/

class Solution:
    def minCosts(self, cost: List[int]) -> List[int]:
        n = len(cost)
        res = []
        left = 0
        left_cost = cost[0]
        for i in range(1, n):
            if (cost[i] < left_cost):
                res += [left_cost] * (i - left)
                left = i
                left_cost = cost[i]
        
        res += [left_cost] * (n - left)
        return res

if __name__ == "__main__":
    cost = [1, 2, 3, 4, 5]
    sol = Solution()
    print(sol.minCosts(cost))  # Output: [1, 1, 1, 1, 1]