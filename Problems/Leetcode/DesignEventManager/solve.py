import heapq
from typing import List

class EventManager:

    def __init__(self, events: list[list[int]]):
        self.map = {}
        self.pq = []
        for event, prio in events:
            heapq.heappush(self.pq, (-prio, event))
            self.map[event] = prio

    def updatePriority(self, event: int, new_prio: int) -> None:
        heapq.heappush(self.pq, (-new_prio, event))
        self.map[event] = new_prio

    def pollHighest(self) -> int:
        while self.pq:
            neg_priority, event = self.pq[0]
            if event not in self.map or self.map[event] != -neg_priority:
                heapq.heappop(self.pq)
            else:
                break

        if not self.pq:
            return -1

        neg_priority, event = heapq.heappop(self.pq)
        del self.map[event]

        return event