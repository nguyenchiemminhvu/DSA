from typing import List

class Solution:
    def latestTimeCatchTheBus(self, buses: List[int], passengers: List[int], capacity: int) -> int:
        n = len(buses)
        m = len(passengers)
        buses.sort()
        passengers.sort()

        ip = 0
        for bus in buses:
            count = 0
            while ip < m and passengers[ip] <= bus and count < capacity:
                count += 1
                ip += 1
        
        if count < capacity:
            res = buses[-1]
        else:
            res = passengers[ip - 1] - 1
        
        s = set(passengers)
        while res in s:
            res -=1
        return res