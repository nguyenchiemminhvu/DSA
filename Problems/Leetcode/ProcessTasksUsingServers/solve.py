from typing import List
import heapq

class Solution:
    def assignTasks(self, servers: List[int], tasks: List[int]) -> List[int]:
        n = len(servers)
        m = len(tasks)
        res = [-1] * m # index of the server tasks[it] is assigned to
        
        pq_server = [(servers[i], i) for i in range(n)] # (weight, index)
        heapq.heapify(pq_server) # available server to process, smallest weight and index

        pq_cooldown = [] # (available_time, weight, index)

        cur_time = 0
        for it in range(m):
            cur_time = max(cur_time, it)
            while pq_cooldown and pq_cooldown[0][0] <= cur_time:
                _, w, idx = heapq.heappop(pq_cooldown)
                heapq.heappush(pq_server, (w, idx))
            
            if not pq_server:
                cur_time = pq_cooldown[0][0]
                while pq_cooldown and pq_cooldown[0][0] <= cur_time:
                    _, w, idx = heapq.heappop(pq_cooldown)
                    heapq.heappush(pq_server, (w, idx))
            
            w, idx = heapq.heappop(pq_server)
            res[it] = idx
            heapq.heappush(pq_cooldown, (cur_time + tasks[it], w, idx))
        
        return res