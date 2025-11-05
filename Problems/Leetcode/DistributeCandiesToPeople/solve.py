from typing import List

class Solution:
    def distributeCandies(self, candies: int, n: int) -> List[int]:
        res = [0] * n
        ir = 0
        cur = 1
        total = 0
        while total < candies:
            ir %= n
            if total + cur >= candies:
                res[ir] += (candies - total)
                break
            else:
                res[ir] += cur
                total += cur
                cur += 1
            ir += 1

        return res