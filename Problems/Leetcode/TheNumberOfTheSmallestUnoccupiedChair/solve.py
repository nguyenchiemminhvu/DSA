from typing import List
import heapq

class Solution:
    def smallestChair(self, times: List[List[int]], target: int) -> int:
        pq = [i for i in range(len(times))] # available seats
        heapq.heapify(pq)

        events = []
        for i, (arrive, leave) in enumerate(times):
            events.append((arrive, 1, i)) # 1 => come
            events.append((leave, 0, i)) # 0 => go
        events.sort(key=lambda x: (x[0], x[1]))

        map_seat = {} # user id -> seat id
        for timestamp, state, i in events:
            if state == 1: # user id i come
                seat = heapq.heappop(pq)
                if i == target:
                    return seat
                map_seat[i] = seat
            else:
                seat = map_seat[i]
                heapq.heappush(pq, seat)
        
        return -1