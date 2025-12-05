from typing import List
from collections import defaultdict

class Solution:
    def hardestWorker(self, n: int, logs: List[List[int]]) -> int:
        m = defaultdict(int)
        res = -1
        prev_time = 0
        max_time = 0
        for i, log in enumerate(logs):
            emp, timestamp = log
            m[emp] = max(m[emp], (timestamp - prev_time))
            if max_time < m[emp]:
                res = emp
                max_time = m[emp]
            elif max_time == m[emp]:
                res = min(res, emp)
            prev_time = timestamp
        return res