from typing import List
from collections import deque

class Employee:
    def __init__(self, id: int, importance: int, subordinates: List[int]):
        self.id = id
        self.importance = importance
        self.subordinates = subordinates

class Solution:
    def getImportance(self, employees: List['Employee'], id: int) -> int:
        emp_map = {emp.id: emp for emp in employees}
        
        res = 0
        q = deque([id])
        while q:
            cur = q.popleft()
            emp = emp_map[cur]
            res += emp.importance
            for adj in emp.subordinates:
                q.append(adj)
        
        return res