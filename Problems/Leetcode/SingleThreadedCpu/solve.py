from types import List
import heapq

class Solution:
    def getOrder(self, tasks: List[List[int]]) -> List[int]:
        n = len(tasks)
        tasks = [(start, dur, i) for i, (start, dur) in enumerate(tasks)]
        tasks.sort(key=lambda x: x[0])

        res = []
        pq = [] # (duration, index)
        i = 0
        cur_time = 0
        while i < n or pq:
            if not pq and cur_time <= tasks[i][0]:
                cur_time = tasks[i][0]

            while i < n and tasks[i][0] <= cur_time:
                start_time, dur, idx = tasks[i]
                heapq.heappush(pq, (dur, idx))
                i += 1

            # push task into order result
            dur, idx = heapq.heappop(pq)
            res.append(idx)
            cur_time += dur
        return res