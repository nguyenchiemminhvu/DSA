from typing import List
import math

class Solution:
    def maxLength(self, nums: List[int]) -> int:
        n = len(nums)
        res = 0
        for i in range(n):
            prod = 1
            lcm = nums[i]
            gcd = nums[i]
            for j in range(i, n):
                prod *= nums[j]
                lcm = math.lcm(lcm, nums[j])
                gcd = math.gcd(gcd, nums[j])
                if prod > 2520 * lcm * gcd:
                    break
                if prod == lcm * gcd:
                    res = max(res, j - i + 1)
        return res