import heapq
from typing import List
from collections import defaultdict

class min_heap:
    def __init__(self):
        self.pq = []
    def push(self, obj):
        heapq.heappush(self.pq, obj)
    def get(self):
        if not self.pq:
            return None
        return self.pq[0]
    def pop(self):
        if not self.pq:
            return None
        return heapq.heappop(self.pq)
    def __bool__(self):
        return True if self.pq else False

class Solution:
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:
        count = defaultdict(int)
        free_rooms = min_heap()
        busy_rooms = min_heap()
        queue = min_heap()
        for start, end in meetings:
            queue.push((start, end))
        for i in range(n):
            free_rooms.push(i)

        while queue:
            start, end = queue.pop()
            duration = end - start

            while busy_rooms and busy_rooms.get()[0] <= start:
                busy_end, room = busy_rooms.pop()
                free_rooms.push(room)
            
            if free_rooms:
                room = free_rooms.pop()
                busy_rooms.push((end, room))
            else:
                busy_end, room = busy_rooms.pop()
                busy_rooms.push((busy_end + duration, room))
            
            count[room] += 1
        
        mx = max(count.values())
        for k, v in count.items():
            if v == mx:
                return k
        return -1
