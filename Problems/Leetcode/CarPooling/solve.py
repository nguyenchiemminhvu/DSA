from typing import List

class Solution:
    def carPooling(self, trips: List[List[int]], cap: int) -> bool:
        events = {}
        for num, start, end in trips:
            if start not in events:
                events[start] = [0, 0]
            if end not in events:
                events[end] = [0, 0]
            events[start][0] += num
            events[end][1] += num
        
        timeline = sorted([(k, v[0], v[1]) for k, v in events.items()])
        cur = 0
        for timestamp, pick, drop in timeline:
            cur -= drop
            cur += pick
            if cur > cap:
                return False

        return True