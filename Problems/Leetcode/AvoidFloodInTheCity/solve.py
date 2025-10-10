from typing import List

class Solution:
    def avoidFlood(self, rains: List[int]) -> List[int]:
        def upper_bound(arr: List[int], target: int) -> int:
            left = 0
            right = len(arr) - 1
            upper_idx = right + 1
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] > target:
                    upper_idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return upper_idx
        
        n = len(rains)
        res = [-1] * n

        last_rain_day = {} # slot -> last_day
        dry_days = []

        for day, slot in enumerate(rains):
            if slot == 0:
                dry_days.append(day)
            else:
                if slot in last_rain_day:
                    # find the first day in dry_days that is greater than last_rain_day[slot]
                    found_day_to_dry = upper_bound(dry_days, last_rain_day[slot])
                    if found_day_to_dry == len(dry_days):
                        return []
                    
                    res[dry_days[found_day_to_dry]] = slot
                    dry_days.pop(found_day_to_dry)
                
                last_rain_day[slot] = day
        
        for day in dry_days:
            res[day] = 1
        
        return res