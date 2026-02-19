from typing import List

class Solution:
    def shipWithinDays(self, nums: List[int], days: int) -> int:
        n = len(nums)

        # check if conveyor belt with capability 'cap'
        # can be used to deliver all packages in 'days' days
        def check_possible(cap: int) -> bool:
            total_day = 1
            cur_load = 0
            for val in nums:
                if cap < val:
                    return False
                if cur_load + val > cap:
                    total_day += 1
                    cur_load = 0
                cur_load += val
            return total_day <= days

        left = 1
        right = sum(nums)
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return res