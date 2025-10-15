from typing import List

class Solution:
    def maximumUnits(self, boxTypes: List[List[int]], truckSize: int) -> int:
        boxTypes.sort(key=lambda b: b[1], reverse=True)
        ib = 0
        res = 0
        while truckSize > 0 and ib < len(boxTypes):
            num_box = min(boxTypes[ib][0], truckSize)
            res += num_box * boxTypes[ib][1]
            truckSize -= num_box
            ib += 1
        return res