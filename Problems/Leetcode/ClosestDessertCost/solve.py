from typing import List

class Solution:
    def closestCost(self, base_costs: List[int], topping_costs: List[int], target: int) -> int:
        def upper_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left, right, found = 0, n - 1, n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    found = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return found

        n = len(base_costs)
        m = len(topping_costs)

        tmp = []
        def dfs(i:int, price:int) -> None:
            if i >= m:
                tmp.append(price)
                return
            
            dfs(i + 1, price)
            dfs(i + 1, price + topping_costs[i])
            dfs(i + 1, price + topping_costs[i] * 2)

        res = float('inf')
        diff = float('inf')
        for base in base_costs:
            tmp = []
            dfs(0, base)
            tmp.sort()
            upper = upper_bound(tmp, target)
            if upper < len(tmp):
                if diff > abs(tmp[upper] - target):
                    diff = abs(tmp[upper] - target)
                    res = tmp[upper]
                elif diff == abs(tmp[upper] - target):
                    res = min(res, tmp[upper])
            if upper > 0:
                if diff > abs(tmp[upper - 1] - target):
                    diff = abs(tmp[upper - 1] - target)
                    res = tmp[upper - 1]
                elif diff == abs(tmp[upper - 1] - target):
                    res = min(res, tmp[upper - 1])
        
        return res