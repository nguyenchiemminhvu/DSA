from typing import List

class Solution:
    def minimumSize(self, nums: List[int], max_op: int) -> int:
        n = len(nums)
        s = sum(nums)

        def check_possible(cap: int) -> bool:
            temp_s = s
            num_bags = 0
            for val in nums:
                if val <= cap:
                    num_bags += 1
                else:
                    num_bags += (val + cap - 1) // cap
            return num_bags - n <= max_op
        
        left = 1
        right = max(nums)
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                right = mid - 1
            else:
                left = mid + 1
        return res