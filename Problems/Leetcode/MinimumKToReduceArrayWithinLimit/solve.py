from typing import List

class Solution:
    def minimumK(self, nums: List[int]) -> int:
        n = len(nums)

        def check_possible(k: int) -> bool:
            op = 0
            for val in nums:
                op += (val + k - 1) // k
            return op <= k ** 2

        low = 1
        high = 10**5
        k = high
        while low <= high:
            mid = low + (high - low) // 2
            if check_possible(mid):
                k = mid
                high = mid - 1
            else:
                low = mid + 1
        
        return k