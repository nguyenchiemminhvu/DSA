from typing import List

class Solution:
    def findRadius(self, houses: List[int], heaters: List[int]) -> int:
        houses.sort()
        heaters.sort()
        
        def check_cover(k: int) -> bool:
            ipos = 0
            ih = 0
            while ipos < len(houses) and ih < len(heaters):
                if abs(houses[ipos] - heaters[ih]) > k:
                    ih += 1
                else:
                    ipos += 1
            return ipos >= len(houses)

        left = 0
        right = 10**9
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_cover(mid):
                res = mid
                right = mid - 1
            else:
                left = mid + 1
        return res