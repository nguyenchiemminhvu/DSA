from typing import List
from collections import deque, defaultdict

class Router:

    def __init__(self, limit: int):
        self.n = limit
        self.s_packets = set() # (time, src, dest)
        self.packets = deque() # (time, src, dest), sorted by time
        self.dest_map = defaultdict(list)

    def addPacket(self, s: int, d: int, t: int) -> bool:
        p = (t, s, d)
        if p in self.s_packets:
            return False
        if len(self.packets) == self.n:
            old_t, old_s, old_d = self.packets.popleft()
            self.s_packets.remove((old_t, old_s, old_d))
            self.dest_map[old_d].pop(0)
        self.packets.append(p)
        self.s_packets.add(p)
        self.dest_map[d].append(t)
        return True

    def forwardPacket(self) -> List[int]:
        if not self.packets:
            return []
        
        t, s, d = self.packets.popleft()
        self.s_packets.remove((t, s, d))
        self.dest_map[d].pop(0)
        return [s, d, t]

    def lower_bound(self, arr, target):
        left, right = 0, len(arr)
        while left < right:
            mid = (left + right) // 2
            if arr[mid] < target:
                left = mid + 1
            else:
                right = mid
        return left
    
    def getCount(self, d: int, start: int, end: int) -> int:
        arr = self.dest_map[d]
        if not arr:
            return 0

        left = self.lower_bound(arr, start)
        right = self.lower_bound(arr, end + 1)
        return right - left


# Your Router object will be instantiated and called as such:
# obj = Router(memoryLimit)
# param_1 = obj.addPacket(source,destination,timestamp)
# param_2 = obj.forwardPacket()
# param_3 = obj.getCount(destination,startTime,endTime)