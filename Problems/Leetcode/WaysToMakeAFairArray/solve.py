from collections import defaultdict
from typing import List

class Solution:
    def waysToMakeFair(self, nums: List[int]) -> int:
        n = len(nums)

        right_odd = defaultdict(int)
        right_even = defaultdict(int)
        
        total = 0
        odd_sum = 0
        even_sum = 0
        for i in range(n - 1, -1, -1):
            right_odd[i] = odd_sum
            right_even[i] = even_sum
            if i & 1:
                odd_sum += nums[i]
            else:
                even_sum += nums[i]
        
        count = 0
        odd_sum = 0
        even_sum = 0
        for i in range(n):
            if odd_sum + right_even[i] == even_sum + right_odd[i]:
                count += 1
            if i & 1:
                odd_sum += nums[i]
            else:
                even_sum += nums[i]
        
        return count