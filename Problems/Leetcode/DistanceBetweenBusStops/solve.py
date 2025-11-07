from typing import List

class Solution:
    def distanceBetweenBusStops(self, distance: List[int], start: int, destination: int) -> int:
        n = len(distance)
        opt1 = 0
        i = start
        while i != destination:
            opt1 += distance[i]
            i = (i + 1) % n
        
        opt2 = 0
        i = start
        while i != destination:
            prev = ((i - 1) + n) % n
            opt2 += distance[prev]
            i = prev
        
        return min(opt1, opt2)