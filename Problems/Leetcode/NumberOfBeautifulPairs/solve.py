from typing import List
import math

class Solution:
    def countBeautifulPairs(self, nums: List[int]) -> int:
        n = len(nums)
        count = 0
        for i in range(n):
            for j in range(i + 1, n):
                a, b = nums[i], nums[j]
                da = int(str(a)[0])
                db = (b % 10)
                if math.gcd(da, db) == 1:
                    count += 1
        return count