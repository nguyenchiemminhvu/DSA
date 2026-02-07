from typing import List
from collections import Counter, deque
import heapq

class Solution:
    def leastInterval(self, tasks: List[str], k: int) -> int:
        counter = Counter(tasks)
        pq = []
        for task, count in counter.items():
            heapq.heappush(pq, (-count, task))
        
        cooldown = deque() # time_available, task, count
        cur_time = 0
        while pq or cooldown:
            cur_time += 1

            while cooldown and cooldown[0][0] <= cur_time:
                timestamp, task, count = cooldown[0]
                heapq.heappush(pq, (-count, task))
                cooldown.popleft()

            if pq:
                neg_count, task = heapq.heappop(pq)
                count = -neg_count
                count -= 1
                if count > 0:
                    cooldown.append((cur_time + k + 1, task, count))
        
        return cur_time