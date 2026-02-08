from typing import List
import heapq

class TaskManager:

    def __init__(self, tasks: List[List[int]]):
        self.task_map = {} # task_id : priority, user
        self.pq = [] # (-priority, -task_id)
        for user, task, priority in tasks:
            self.add(user, task, priority)

    def add(self, user_id: int, task_id: int, priority: int) -> None:
        self.task_map[task_id] = (priority, user_id)
        heapq.heappush(self.pq, (-priority, -task_id))

    def edit(self, task_id: int, new_prio: int) -> None:
        _, user_id = self.task_map[task_id]
        self.task_map[task_id] = (new_prio, user_id)
        heapq.heappush(self.pq, (-new_prio, -task_id))

    def rmv(self, task_id: int) -> None:
        self.task_map.pop(task_id)

    def execTop(self) -> int:
        while self.pq and (-self.pq[0][1] not in self.task_map or -self.pq[0][0] != self.task_map[-self.pq[0][1]][0]):
            heapq.heappop(self.pq)
        
        if not self.pq:
            return -1
        neg_prio, neg_id = heapq.heappop(self.pq)
        task_id = -neg_id
        user_id = self.task_map[task_id][1]
        self.task_map.pop(task_id)
        return user_id

# Your TaskManager object will be instantiated and called as such:
# obj = TaskManager(tasks)
# obj.add(userId,taskId,priority)
# obj.edit(taskId,newPriority)
# obj.rmv(taskId)
# param_4 = obj.execTop()